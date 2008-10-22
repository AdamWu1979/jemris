function [SeqTree,ax]=plotseq(handles,moment_flag,kspace_flag)
%[SeqTree,ax]=plotseq(handles,moment_flag,kspace_flag)
%helper function of the JEMRIS_seq GUI - called for every redraw
%input : GUI handles and flags, if moments / k-space are drawn  
%output: Sequence tree and axes limts for the seuqence diagram

%TS@IME-FZJ 03/2007

hax=handles.hax;
ax=handles.ax;
SeqTree=[];
zoom(gcf,'off');
set(handles.zoomFlag,'Value',0);

% 1st: draw sequence tree
if handles.plotSD==0
    set(handles.seq_dump,'Visible','on');
    set(handles.kspace_flag,'Visible','off');
    set(handles.draw_moments,'Visible','off');
    set(handles.show_interval,'Visible','off');
    set(handles.addADCs,'Visible','off');
    set(handles.ContDraw,'Visible','off');
    set(handles.text8,'Visible','off');
    set(handles.text9,'Visible','on');
    set(handles.zoomFlag,'Visible','off');
    set(handles.DrawSD,'Value',0);
    axes(hax{7}); cla(hax{7},'reset');
    SeqTree=plotSeqTree(handles.Seq,handles);
    for i=1:6;cla(hax{i},'reset');set(hax{i},'visible','off');end
    cla(hax{8},'reset');set(hax{8},'visible','off')
    return;
else
    set(handles.text9,'Visible','off');
    cla(hax{7},'reset');
    set(hax{7},'visible','off')
    set(handles.seq_dump,'Visible','off');
end

% rest of the file: draw sequence pulse diagram or k-space trajecotry
if nargin<3;kspace_flag=0;end
set(handles.kspace_flag,'Visible','on');
set(handles.zoomFlag,'Visible','on')
vis_set(handles.draw_moments ,kspace_flag==0);
vis_set(handles.show_interval,kspace_flag==0);
vis_set(handles.text8        ,kspace_flag==0);
vis_set(handles.addADCs      ,kspace_flag~=0);
vis_set(handles.ContDraw     ,kspace_flag~=0 || handles.dm ~=0);
if kspace_flag==0;cla(hax{8},'reset');set(hax{8},'visible','off');end

f=fopen('seq.bin'); A=fread(f,Inf,'double'); fclose(f); if A(1)==-1;return;end
%A(end)=[];
n=size(A,1)/7;A=reshape(A,7,n)'; A=[0 -1 0 0 0 0 0;A];

t=A(:,1);
Iadc=find(A(:,2)>=0);
Tadc=t(Iadc);
Rec_Phs=A(Iadc,2)*180/pi;
A=A(:,[3:7]); A(:,2)=A(:,2)*180/pi;
 
if length(ax)==1;ax=[min(t) max(t)];end

DO_2D = isempty(find(A(:,5))); 
[dummy,i1]=min(abs(t-ax(1)));
[dummy,i2]=min(abs(t-ax(2)));

if moment_flag
    A(:,[3 4 5])=cumtrapz(t,A(:,[3 4 5]));
    %set moment to zero after every RF pulse
    J=find(diff(A(:,1)));J=J(2:2:end);
    if handles.cd==1; J=2; end
    for j=1:length(J)
        fact=1; %try to guess phase inversions from 180 degree pulses!
        if abs(pi-trapz(t(J(j)-1:J(j)),A(J(j)-1:J(j),1)))<1e-4;fact=2;end
        A(J(j)+1:end,3)=A(J(j)+1:end,3)-fact*A(J(j),3);
        A(J(j)+1:end,4)=A(J(j)+1:end,4)-fact*A(J(j),4);
        A(J(j)+1:end,5)=A(J(j)+1:end,5)-fact*A(J(j),5);
    end
    if kspace_flag
        if handles.cd==1; J=[1:20:size(A,1)]'; else;J=[0;J]; end
        for i=1:6;cla(hax{i},'reset');set(hax{i},'visible','off');end
        axes(hax{8});cla(hax{8},'reset');set(gca,'visible','on');hold on
        C=flipud(autumn(length(J)));
        for j=1:length(J)
            if j<length(J);n_end=J(j+1)-1+handles.cd;else n_end=length(A(:,3));end
            n_all=[J(j)+1-handles.cd:1:n_end];
            if DO_2D
                plot(A(n_all,3),A(n_all,4),'color',C(j,:))
            else
                plot3(A(n_all,3),A(n_all,4),A(n_all,5),'color',C(j,:)),view(3),grid
            end
        end
        if kspace_flag==2;
            if DO_2D
                plot(A(Iadc,3),A(Iadc,4),'.g')
            else
                plot3(A(Iadc,3),A(Iadc,4),A(Iadc,5),'.g')
            end
        end 
        set(gca,'color',[0 0 0]);
        if (min(A(:,3))<max(A(:,3)) && min(A(:,4))<max(A(:,4)) )
            axis(1.1*[min(A(:,3)) max(A(:,3)) min(A(:,4)) max(A(:,4))]);
        end
        axis equal; hold off;
        xlabel('Kx [rad / mm]','fontsize',12,'fontweight','bold')
        ylabel('Ky [rad / mm]','fontsize',12,'fontweight','bold')
        if ~DO_2D
            hgca=gca; save tmp hgca
            zlabel('Kz [rad / mm]','fontsize',12,'fontweight','bold')
            set(gca,'xcolor',[.5 .5 .5],'ycolor',[.5 .5 .5],'zcolor',[.5 .5 .5])
        end

        if length(J)>2
            colormap(C);h=colorbar;set(h,'ytick',[],'color',[0 0 0]);
            axes(h);xlabel('early','color',[0 0 0]);title('late','color',[0 0 0])
        end
        return
    end
end

J=find(Tadc>ax(1) & Tadc<ax(2));
Tadc=Tadc(J);
Rec_Phs=Rec_Phs(J);

if i1>1,i1=i1-1;end
if i2<length(t),i2=i2+1;end
I=i1:i2;

YL={'ADC','|RF|','RF{\phi}','GX','GY','GZ'};
cla(hax{1},'reset');axes(hax{1}),plot(Tadc,Rec_Phs,'.r'),set(gca,'ytick',[],'xticklabel',[])
set(gca,'xlim',[ax(1) ax(2)],'ylim',[-180 180]),grid
ylabel(YL{1},'fontsize',14,'fontweight','bold')

for i=1:5
 cla(hax{i+1},'reset');axes(hax{i+1}),plot(t(I),A(I,i),'linewidth',2),grid
 ylabel(YL{i+1},'fontsize',14,'fontweight','bold')
 set(gca,'xlim',[ax(1) ax(2)])
 ay=get(gca,'ylim');
 if abs(ay(1)-ay(2))<1e-10,set(gca,'ylim',100*ay);end
 if (i==2 || i==5),xlabel('t [msec]','fontsize',12),else set(gca,'xticklabel',[]),end
end


if (nargout==0);clear t;end
return

%%%
function vis_set(h,b)
if b
    set(h,'Visible','on');
else
    set(h,'Visible','off');
end