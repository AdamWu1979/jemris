/**************************************************************************
** Copyright (c) 2003-2005                                               **
** Forschungszentrum Juelich GmbH, Federal Republic of Germany.          **
**                                                                       **
** See the file `var_array.c',                                           **
**              `list_c.h', or                                           **
**              `var_array++_cpp.h' for details                          **
**************************************************************************/

/*
 * This file is part of the VarArray library, version 1.0.
 *
 * Authors:
 *  Guenter Egerer, Annika Schiller, Forschungszentrum Juelich
 * Bugs:
 *  Please report any bugs to `G.Egerer@fz-juelich.de'.
 */

/*************************************************************************/
/*                                                                       */
/* Name: Annika Schiller       Telefon: 3439         Institut: ZAM       */
/* Datum  : 13.12.2004                                                   */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/* Header : array                                                        */
/* Aufgabe: enth�lt Funktionen zum Anlegen, L�schen und Abfragen der     */
/*          der Dimensionsl�ngen von mehrdimensionalen Felder            */
/* Definierte Funktionen:                                                */
/*        - vaCreate_2d                                                  */
/*        - vaDelete                                                     */
/*        - vaSize                                                       */
/*                                                                       */
/*************************************************************************/

#ifndef VAR_ARRAY_H_INCLUDED
#define VAR_ARRAY_H_INCLUDED

/* --------------------------------------------------------------------- */
/* Funktionsdeklarationen                                                */
/* --------------------------------------------------------------------- */

/* --------------------------------------------------------------------- */
/* Funktion vaCreate_1d()                                                */
/*    erzeugt ein eindimensionales Feld mit 'dim1' Elementen, die Spei-  */
/*    chergr��e eines Elementes wird festgelegt durch die �bergebene     */
/*    Gr��e 'element_size'                                               */
/* Parameter: Dimensionsl�nge, element_size, Anfangspointer              */
/* R�ckgabe : generischer Zeiger auf das erste Element des erzeugten     */
/*            Feldes                                                     */
/* --------------------------------------------------------------------- */
extern void *vaCreate_1d ( int dim1, size_t element_size, void *begin);

#define vaArray_1d(type_name) type_name *

#define vaCreate_1d(dim1, type_name, ptr_to_storage)       \
          (  ( vaArray_1d(type_name) ) vaCreate_1d((dim1), \
                                        sizeof(type_name),(ptr_to_storage))  )

/* --------------------------------------------------------------------- */
/* Funktion vaCreate_2d()                                                */
/*    erzeugt ein mehrdimensionales Feld mit 'dim1' Zeilen und           */
/*    'dim2' Spalten, die Speichergr��e eines Elementes wird fest-       */
/*    gelegt durch die �bergebene Gr��e 'element_size'                   */
/* Parameter: Dimensionsl�ngen, element_size, Anfangspointer             */
/* R�ckgabe : generischer Zeiger auf die erste Zeile des erzeugten       */
/*            Feldes                                                     */
/* --------------------------------------------------------------------- */
extern void *vaCreate_2d ( int dim1, int dim2, size_t element_size, 
			       const void *begin);

#define vaArray_2d(type_name) type_name *const *

#define vaCreate_2d(dim1, dim2, type_name, ptr_to_storage)                 \
          (  ( vaArray_2d(type_name) ) vaCreate_2d((dim1), (dim2),         \
                                        sizeof(type_name),(ptr_to_storage))  )

/* --------------------------------------------------------------------- */
/* Funktion vaCreate_3d()                                                */
/*    erzeugt ein 3-dimensionales Feld mit den Dimensionen 'dim1', 'dim2'*/
/*    und 'dim3', die Speichergr��e eines Elementes wird fest-           */
/*    gelegt durch die �bergebene Gr��e 'element_size'                   */
/* Parameter: Dimensionsl�ngen, element_size, Anfangspointer             */
/* R�ckgabe : generischer Zeiger auf die erste Zeile des erzeugten       */
/*            Feldes                                                     */
/* --------------------------------------------------------------------- */

extern void *vaCreate_3d ( int dim1, int dim2, int dim3, size_t element_size,
			       const void *begin_);

#define vaArray_3d(typ_name) typ_name *const *const *

#define vaCreate_3d(dim1, dim2, dim3, type_name, ptr_to_storage)           \
          (  ( vaArray_3d(type_name) ) vaCreate_3d((dim1), (dim2), (dim3), \
                                        sizeof(type_name),(ptr_to_storage))  )

/* --------------------------------------------------------------------- */
/* Funktion vaCreate_4d()                                                */
/*    erzeugt ein 4-dimensionales Feld mit den Dimensionen 'dim1',       */
/*    'dim2', 'dim3' und 'dim4', die Speichergr��e eines Elementes wird  */
/*    festgelegt durch die �bergebene Gr��e 'element_size'               */
/* Parameter: Dimensionsl�ngen, element_size, Anfangspointer             */
/* R�ckgabe : generischer Zeiger auf die erste Zeile des erzeugten       */
/*            Feldes                                                     */
/* --------------------------------------------------------------------- */

extern void *vaCreate_4d ( int dim1, int dim2, int dim3, int dim4, 
                               size_t element_size, const void *begin_);

#define vaArray_4d(typ_name) typ_name *const *const *const *

#define vaCreate_4d(dim1, dim2, dim3, dim4, type_name, ptr_to_storage)       \
          (  ( vaArray_4d(type_name) ) vaCreate_4d((dim1), (dim2), (dim3),   \
                                    (dim4), sizeof(type_name),(ptr_to_storage)) )

/* --------------------------------------------------------------------- */
/* Funktion vaCreate_5d()                                                */
/*    erzeugt ein 5-dimensionales Feld mit den Dimensionen 'dim1',       */
/*    'dim2', 'dim3', 'dim4' und 'dim5',  die Speichergr��e eines        */
/*    Elementes wird festgelegt durch die �bergebene Gr��e 'element_size'*/
/* Parameter: Dimensionsl�ngen, element_size, Anfangspointer             */
/* R�ckgabe : generischer Zeiger auf die erste Zeile des erzeugten       */
/*            Feldes                                                     */
/* --------------------------------------------------------------------- */

extern void *vaCreate_5d ( int dim1, int dim2, int dim3, int dim4, int dim5, 
                               size_t element_size, const void *begin_);

#define vaArray_5d(typ_name) typ_name *const *const *const *const *

#define vaCreate_5d(dim1, dim2, dim3, dim4, dim5, type_name, ptr_to_storage) \
          (  ( vaArray_5d(type_name) ) vaCreate_5d((dim1), (dim2), (dim3),   \
                            (dim4), (dim5), sizeof(type_name),(ptr_to_storage)) )

/* --------------------------------------------------------------------- */
/* Funktion vaDelete()                                                   */
/*    gibt den Speicherplatz des dynamisch angelegten Feldes, auf den    */
/*    key zeigt, wieder frei                                             */
/* Parameter: Anfangszeiger des zu l�schenden Feldes                     */
/* R�ckgabe : keine                                                      */
/* --------------------------------------------------------------------- */
extern void vaDelete ( const void *start );

/* --------------------------------------------------------------------- */
/* Funktion vaSize()                                                     */
/*    liefert zu einem Zeiger auf ein Feld die Dimensionsl�nge der       */
/*    Dimension 'dim'                                                    */
/* Parameter: Zeiger auf ein Feld, Dimension                             */
/* R�ckgabe : Gr��e der Dimension, falls der Schl�ssel gefunden wurde    */
/*            -1, falls der Schl�ssel nicht gefunden wurde               */
/* --------------------------------------------------------------------- */
extern int vaSize ( const void *key, int dim );

#endif   /* VAR_ARRAY_H_INCLUDED */
