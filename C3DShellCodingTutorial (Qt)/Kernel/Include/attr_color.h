////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Атрибуты. Цвет. Толщина линий отрисовки. Стиль линий отрисовки. Свойства для OpenGL.
         \en Attributes. Color. Thickness of drawing lines. Style of drawing lines. Properties for OpenGL. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __ATTR_COLOR_H
#define __ATTR_COLOR_H


#include <attr_elementary_attribut.h>
#include <mb_variables.h>


#define __RGB__  3


//------------------------------------------------------------------------------
/** \brief \ru Преобразовать цвет по трём компонентам в uint32.
           \en Convert a color by 3 components in uint32. \~
  \details
  \warning \ru Значения компонент цвета должны лежать в диапазоне [ 0; 1 ].
           \en Values of color components should belong to the range [ 0; 1 ]. \~
  \ingroup Model_Attributes
*/
// ---
inline uint32 RGB2uint32( double r, double g, double b )
{ 
  const double f1 = 255.0 / 256.0;
  uint32 uinturgb[3];
  const uint32 bt = 256;
  uinturgb[0] = uint32 ( 256.0 * r * f1 );
  uinturgb[1] = uint32 ( 256.0 * g * f1 );
  uinturgb[2] = uint32 ( 256.0 * b * f1 );
  for ( int n = 0; n < 3; n++ )
    if ( uinturgb[n] >= bt ) {
      uinturgb[n] = bt - 1;
      C3D_ASSERT_UNCONDITIONAL( false );
    }
  return uinturgb[0] + bt * ( uinturgb[1] + bt * uinturgb[2] ); 
}


//------------------------------------------------------------------------------
/** \brief \ru Преобразовать unit32 в три компоненты цвета.
           \en Convert unit32 to 3 components of color. \~
  \details
  \warning \ru Компоненты цветов лежат в диапазоне [ 0; 1 ].
           \en Color components belong to the range [ 0; 1 ]. \~
  \ingroup Model_Attributes
*/
// ---
template<typename float_t>
void uint322RGB( uint32 color, float_t& r, float_t& g, float_t& b ) { 
  const float_t r255 = float_t(1.0 / 255.0);
  const uint32 u256 = (uint32)SYS_MAX_UINT8 + 1;
  r = float_t ( color           % u256); 
  g = float_t ( (color / 256)   % u256); 
  b = float_t ( (color / 65536) % u256); 
  r *= r255; g *= r255; b *= r255; 
}


//------------------------------------------------------------------------------
/** \brief \ru Цвет.
           \en Color. \~
  \details \ru Цвет. \n
           \en Color. \n \~
  \ingroup Model_Attributes
*/
// ---
class MATH_CLASS MbColor : public MbElementaryAttribute {
protected :
  uint32 color; ///< \ru Цвет. \en Color. 

protected :
  /// \ru Конструктор копирования. \en Copy constructor. 
  MbColor( const MbColor & init ); 
public :
  /// \ru Конструктор. \en Constructor. 
  MbColor( uint32 init ); 
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbColor();

  // \ru Общие функции объекта \en Common functions of object. 

  virtual MbeAttributeType AttributeType() const; // \ru Дать подтип атрибута. \en Get subtype of an attribute. 

  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ); // \ru Инициализировать данные по присланным. \en Initialize data. 

          /// \ru Установить цвет. \en Set a color. 
          void    Init( uint32 init ) { color = init; }
          /// \ru Дать цвет. \en Get a color. 
          uint32  Color() const { return color; }
//int         R() const { return red;   } // \ru Красный цвет \en Red color  
//int         G() const { return green; } // \ru Зеленый цвет \en Green color  
//int         B() const { return blue;  } // \ru Синий   цвет \en Blue color  

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

private:
          void        operator = ( const MbColor & ); // \ru Не реализовано \en Not implemented 

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbColor ) 
}; // MbColor

IMPL_PERSISTENT_OPS( MbColor )


//------------------------------------------------------------------------------
/** \brief \ru Толщина линий отрисовки.
           \en Thickness of drawing lines. \~
  \details \ru Толщина линий отрисовки. \n
           \en Thickness of drawing lines. \n \~
  \ingroup Model_Attributes
*/
// ---
class MATH_CLASS MbWidth : public MbElementaryAttribute {
protected :
  int width; ///< \ru Толщина линий отрисовки. \enThickness of drawing lines. 

protected :
  /// \ru Конструктор копирования. \en Copy constructor. 
  MbWidth( const MbWidth & init ); 
public :
  /// \ru Конструктор. \en Constructor. 
  MbWidth( int init );
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbWidth();

  // \ru Общие функции объекта \en Common functions of object. 

  virtual MbeAttributeType AttributeType() const; // \ru Дать подтип атрибута. \en Get subtype of an attribute. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ); // \ru Инициализировать данные по присланным. \en Initialize data. 

          /// \ru Установить толщину. \en Set a thickness. 
          void    Init( int init ) { width = init; }
          /// \ru Дать толщину. \en Get a thickness. 
          int     Width() const  { return width; }

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

private:
          void        operator = ( const MbWidth & ); // \ru Не реализовано \en Not implemented 

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbWidth ) 
}; // MbWidth

IMPL_PERSISTENT_OPS( MbWidth )


//------------------------------------------------------------------------------
/** \brief \ru Стиль линий отрисовки.
           \en Style of drawing lines. \~
  \details \ru Стиль линий отрисовки. \n
           \en Style of drawing lines. \n \~
  \ingroup Model_Attributes
*/
// ---
class MATH_CLASS MbStyle : public MbElementaryAttribute {
protected :
  int style; ///< \ru Стиль линий отрисовки. \en Style of drawing lines. 

protected :
  /// \ru Конструктор копирования. \en Copy constructor. 
  MbStyle( const MbStyle & init ); 
public :
  /// \ru Конструктор. \en Constructor. 
  MbStyle( int init );
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbStyle();

  // \ru Общие функции объекта \en Common functions of object. 

  virtual MbeAttributeType AttributeType() const; // \ru Дать подтип атрибута. \en Get subtype of an attribute. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ); // \ru Инициализировать данные по присланным. \en Initialize data. 

          /// \ru Установить стиль линий отрисовки. \en Set style of drawing lines. 
          void    Init( int init ) { style = init; }
          /// \ru Дать стиль линий отрисовки. \en Get style of drawing lines. 
          int     Style() const  { return style; }

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

private:
          void        operator = ( const MbStyle & ); // \ru Не реализовано \en Not implemented 

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbStyle ) 
}; // MbStyle

IMPL_PERSISTENT_OPS( MbStyle )


//------------------------------------------------------------------------------
/** \brief \ru Свойства для OpenGL.
           \en Properties for OpenGL. \~
  \details \ru Свойства для OpenGL для трех цветов: RED, GREEN, BLUE. \n
           \en Properties for OpenGL for colors: RED, GREEN, BLUE. \n \~
  \ingroup Model_Attributes
*/
// ---
class MATH_CLASS MbVisual : public MbElementaryAttribute {
protected :
  float ambient[__RGB__];     ///< \ru Коэффициент общего фона для трех цветов: RED, GREEN, BLUE. \en Coefficient of ambient background for colors: RED, GREEN, BLUE, range 0.0 - 1.0. 
  float diffuse[__RGB__];     ///< \ru Коэффициент диффузного отражения для трех цветов: RED, GREEN, BLUE. \en Coefficient of diffuse reflection for colors: RED, GREEN, BLUE, range 0.0 - 1.0. 
  float specularity[__RGB__]; ///< \ru Коэффициент зеркального отражения света трех цветов: RED, GREEN, BLUE. \en Coefficient of specular reflection for light colors: RED, GREEN, BLUE, range 0.0 - 1.0. 
  float shininess;            ///< \ru Блеск (показатель степени в законе зеркального отражения). \en Shininess (index according to the law of specular reflection), range 0 - 128. 
  float opacity;              ///< \ru Коэффициент непрозрачности (коэффициент суммарного отражения). \en Opacity coefficient (coefficient of total reflection), range 0.0 (transparent) - 1.0(opaque). 
  float emission;             ///< \ru Коэффициент излучения. \en Emissivity coefficient, range 0.0 - 1.0. 
  float chrom;                ///< \ru Коэффициент зеркального отражения объектов. \en Coefficient of specular reflection for objects, range 0.0 - 1.0. 

protected :
  /// \ru Конструктор копирования. \en Copy constructor. 
  MbVisual( const MbVisual & init ); 
public :
  /// \ru Конструктор. \en Constructor. 
  MbVisual( float a = MB_AMBIENT, float d = MB_DIFFUSE, float s = MB_SPECULARITY,
            float h = MB_SHININESS, float t = MB_OPACITY, float e = MB_EMISSION ); 
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbVisual();

  // \ru Общие функции объекта \en Common functions of object. 

  virtual MbeAttributeType AttributeType() const; // \ru Дать подтип атрибута. \en Get subtype of an attribute. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ); // \ru Инициализировать данные по присланным. \en Initialize data. 

          /// \ru Установить свойства для OpenGL. \en Set properties for OpenGL. 
          void    Init( float a = MB_AMBIENT, float d = MB_DIFFUSE, float s = MB_SPECULARITY, 
			                  float h = MB_SHININESS, float t = MB_OPACITY, float e = MB_EMISSION, uint rgb = 0 ) { 
                    ambient[rgb%__RGB__]     = a; // \ru Коэффициент общего фона. \en Coefficient of ambient background. 
                    diffuse[rgb%__RGB__]     = d; // \ru Коэффициент диффузного отражения. \en Coefficient of diffuse reflection. 
                    specularity[rgb%__RGB__] = s; // \ru Коэффициент зеркального отражения света. \en Coefficient of specular reflection for light. 
                    shininess   = h; // \ru Блеск (показатель степени. в законе зеркального отражения). \en Shininess (index according to the law of specular reflection). 
                    opacity     = t; // \ru Коэффициент непрозрачности. \en Opacity coefficient. 
                    emission    = e; // \ru Коэффициент излучения. \en Emissivity coefficient. 
                    chrom       = s; // \ru Коэффициент зеркального отражения объектов. \en Coefficient of specular reflection for objects. 
                  }
          /// \ru Дать свойства для OpenGL. \en Get properties for OpenGL. 
          void    Get( float & a, float & d, float & s, float & h, float & t, float & e, uint rgb = 0 ) const { 
                    a = ambient[rgb%__RGB__];     // \ru Коэффициент общего фона. \en Coefficient of ambient background. 
                    d = diffuse[rgb%__RGB__];     // \ru Коэффициент диффузного отражения. \en Coefficient of diffuse reflection. 
                    s = specularity[rgb%__RGB__]; // \ru Коэффициент зеркального отражения света. \en Coefficient of Specular reflection for light. 
                    h = shininess;   // \ru Блеск (показатель степени в законе зеркального отражения). \en Shininess (index according to the law of specular reflection). 
                    t = opacity;     // \ru Коэффициент непрозрачности. \en Opacity coefficient. 
                    e = emission;    // \ru Коэффициент излучения. \en Emissivity coefficient. 
                  }
          float   Ambient     ( uint rgb = 0 ) const { return ambient[rgb%__RGB__];     } // \ru Дать коэффициент общего фона. \en Get a coefficient of ambient background. 
          float   Diffuse     ( uint rgb = 0 ) const { return diffuse[rgb%__RGB__];     } // \ru Дать коэффициент диффузного отражения. \en Get a coefficient of diffuse reflection. 
          float   Specularity ( uint rgb = 0 ) const { return specularity[rgb%__RGB__]; } // \ru Дать коэффициент зеркального отражения света. \en Get a coefficient of specular reflection for light. 
          float   Shininess   () const { return shininess; } // \ru Дать блеск (показатель степени в законе зеркального отражения). \en Get shininess (index according to the law of specular reflection). 
          float   Opacity     () const { return opacity;   } // \ru Дать коэффициент непрозрачности. \en Get an opacity coefficient. 
          float   Emission    () const { return emission;  } // \ru Дать коэффициент излучения. \en Get a coefficient of emissivity. 
          float   Chrom       () const { return chrom;     } // \ru Дать коэффициент зеркального отражения объектов. \en Get a coefficient of specular reflection for objects. 
  const   float * Ambients () const { return ambient;      } // \ru Дать коэффициенты общего фона. \en Get all coefficients of ambient background. 
  const   float * Diffuses () const { return diffuse;      } // \ru Дать коэффициенты диффузного отражения. \en Get all coefficients of diffuse reflection. 
  const   float * Specularitys() const { return specularity; } // \ru Дать коэффициенты зеркального отражения света. \en Get all coefficients of specular reflection for light. 

          void    SetAmbient     ( float v, uint rgb = 0 ) { ambient[rgb%__RGB__] = v;     } // \ru Установить коэффициент общего фона. \en Set a coefficient of ambient background. 
          void    SetDiffuse     ( float v, uint rgb = 0  ) { diffuse[rgb%__RGB__] = v ;    } // \ru Установить коэффициент диффузного отражения. \en Set a coefficient of diffuse reflection. 
          void    SetSpecularity ( float v, uint rgb = 0  ) { specularity[rgb%__RGB__] = v; } // \ru Установить коэффициент зеркального отражения света. \en Set a coefficient of specular reflection for light. 
          void    SetShininess   ( float v ) { shininess = v;   } // \ru Установить блеск (показатель степени в законе зеркального отражения). \en Set shininess (index according to the law of specular reflection). 
          void    SetOpacity     ( float v ) { opacity = v;     } // \ru Установить коэффициент непрозрачности. \en Set an opacity coefficient. 
          void    SetEmission    ( float v ) { emission = v;    } // \ru Установить коэффициент излучения. \en Set a coefficient of emissivity. 
          void    SetChrom       ( float v ) { chrom = v;       } // \ru Установить коэффициент зеркального отражения объектов. \en Set a coefficient of specular reflection for objects. 

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

private:
          void        operator = ( const MbVisual & ); // \ru Не реализовано \en Not implemented 

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbVisual ) 
}; // MbVisual

IMPL_PERSISTENT_OPS( MbVisual )


//------------------------------------------------------------------------------
/** \brief \ru Количество u-линий и v-линий отрисовочной сетки.
           \en The number of u-mesh and v-mesh drawing lines. \~
  \details \ru Количество u-линий и v-линий отрисовочной сетки. \n
           \en The number of u-mesh and v-mesh drawing lines. \n \~
  \ingroup Model_Attributes
*/
// ---
class MATH_CLASS MbWireCount : public MbElementaryAttribute {
protected :
  size_t uMeshCount; ///< \ru Количество u-линий отрисовочной сетки. \en The number of u-mesh lines. 
  size_t vMeshCount; ///< \ru Количество v-линий отрисовочной сетки. \en The number of v-mesh lines. 

protected :
  /// \ru Конструктор копирования. \en Copy constructor. 
  MbWireCount( const MbWireCount & init ); 
public :
  /// \ru Конструктор. \en Constructor. 
  MbWireCount( size_t uCount, size_t vCount );
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbWireCount();

  // \ru Общие функции объекта \en Common functions of object. 

  virtual MbeAttributeType AttributeType() const; // \ru Дать подтип атрибута. \en Get subtype of an attribute. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ); // \ru Инициализировать данные по присланным. \en Initialize data. 

          /// \ru Установить количество линий отрисовки. \en Set count of drawing lines. 
          void    Init( size_t uCount, size_t vCount ) { uMeshCount = uCount, vMeshCount = vCount; }
          /// \ru Выдать количество разбиений по u и v. \en The the number of splittings in u-direction and v-direction. 
          void    Get( size_t & uCount, size_t & vCount ) const { uCount = uMeshCount; vCount = vMeshCount; }

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

private:
          void        operator = ( const MbWireCount & ); // \ru Не реализовано \en Not implemented 

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbWireCount ) 
}; // MbWireCount

IMPL_PERSISTENT_OPS( MbWireCount )


#endif // __ATTR_COLOR_H
