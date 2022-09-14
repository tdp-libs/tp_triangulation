#ifndef tp_triangulation_Globals_h
#define tp_triangulation_Globals_h

#include "tp_utils/Globals.h" // IWYU pragma: keep

#if defined(TP_TRIANGULATION_LIBRARY)
#  define TP_TRIANGULATION_SHARED_EXPORT TP_EXPORT
#else
#  define TP_TRIANGULATION_SHARED_EXPORT TP_IMPORT
#endif

//##################################################################################################
//! An interface for performing polygon triangulation.
/*!

*/
namespace tp_triangulation
{
}

#endif
