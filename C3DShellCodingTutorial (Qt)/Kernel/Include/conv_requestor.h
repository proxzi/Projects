////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Интерфейс запроса масштаба. Интерфейс запроса сшивки.
         \en Interface of scale request. Interface of stitching request. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CONV_REQUESTOR_H
#define __CONV_REQUESTOR_H


#include <reference_item.h>


//------------------------------------------------------------------------------
/// \ru Интерфейс запроса масштаба. \en Interface of scale request. 
// ---
struct IScaleRequestor : public MbRefItem
{
  virtual double ScaleRequest() = 0;
};


//------------------------------------------------------------------------------
/// \ru Интерфейс запроса сшивки. \en Interface of stitching request. 
// ---
struct IStitchRequestor : public MbRefItem
{
  virtual bool StitchRequest() = 0;
};


#endif // __CONV_REQUESTOR_H
