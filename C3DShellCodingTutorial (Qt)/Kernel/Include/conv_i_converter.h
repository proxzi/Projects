////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Интерфейсы конвертера.
         \en Interfaces of the converter. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CONV_I_CONVERTER_H
#define __CONV_I_CONVERTER_H


#include <math_define.h>
#include <tool_cstring.h>
#include <conv_error_result.h>
#include <mb_data.h>
#include <map>
#include <vector>


class             IProgressIndicator;
struct            IScaleRequestor;
class             ItModelDocument;
class  MATH_CLASS MbRefItem;
class  MATH_CLASS MbPlacement3D;
class  MATH_CLASS MbModel;


/** 
  \addtogroup Exchange_Interface
  \{
*/


//------------------------------------------------------------------------------
/** \brief \ru Интерфейс свойств конвертера.
           \en Interface of converter's properties. \~
  \details \ru Интерфейс свойств конвертера реализует выдачу имени документа и других сведений о нём, таких как автор,
    и управление режимами работы - сшивкой поверхностей с возможностью создания твёрдых 
    тел, фильтрацией объектов, формирование журнала трансляции.
           \en Interface of converter's properties realizes getting the document's name and other information about it, such as the author,
    and management of modes of operations - stitching of surfaces with possibility of solids creation, 
    objects filtration, generation of translation journal. \~
\ingroup Exchange_Interface
*/
class IConvertorProperty3D {
public :
  virtual ~IConvertorProperty3D() {}

public:
  /// \ru Получить имя документа. \en Get document's name. 
  virtual const std::string GetDocumentName   () const = 0; //{ return std::string( GetDocName().get_str() ); };
  /// \ru Получить имя файла для конвертирования. \en Get file name for converting. 
  virtual const c3d::path_string FullFilePath  () const = 0 ;//{ return c3d::path_string( GetFileName().c_str() ); };
  /// \ru Является ли файл текстовым. \en Whether the file is a text file. 
  virtual bool           IsFileAscii      () const = 0; 
  /// \ru Получить версию формата при экспорте. \en Get the version of format for export.
  virtual long int       GetFormatVersion () const { return EXPORT_DEFAULT; };
  /// \ru Задать формат для экспорта \en Set format for export 
  DEPRECATE_DECLARE virtual MbeImpExpFormat GetFormat       () const { return ief_STEP203; }
  /// \ru Следует ли экспортировать только поверхности ( введено для работы конвертера IGES ). \en Whether to export only surfaces (introduced for work with converter IGES ). 
  virtual bool           IsOutOnlySurfaces() const = 0;
  /// \ru Является ли экспортируемый документ сборкой. \en Whether the document for export is an assembly. 
  virtual bool           IsAssembling     () const = 0; 
  /// \ru Получить значение разрешения на импорт экспорт объектов определенного типа. \en Get the value of permission for import-export of objects of a certain type. 
  virtual bool           GetIoPermission( MbeIOPermiss nPermission ) const = 0; 
  /// \ru Получить значения разрешений на импорт экспорт объектов определенных типов. \en Get values of permission for import-export of objects of certain types. 
  virtual void           GetIoPermissions( std::vector<bool>& ioPermissions ) const = 0; 
  /// \ru Установить разрешение на импорт экспорт объектов определенного типа. \en Set permission for import-export of objects of a certain type. 
  virtual void           SetIoPermission( MbeIOPermiss nPermission, bool set ) = 0; 
  /// \ru Получить значение специфичной строки для конвертера. \en Get the value of a certain string for the converter. 
  virtual bool           GetPropertyString ( MbeConverterStrings nString, std::string &  propertyString ) const = 0;
  /// \ru Установить значение специфичной строки для конвертера. \en Set the value of a certain string for the converter. 
  virtual void           SetPropertyString ( MbeConverterStrings nString, const std::string &  propertyString ) = 0;
  /// \ru Представление текста в аннотационных объектах. \en Text representation in annotation objects. 
  virtual eTextForm      GetAnnotationTextRepresentation () const { return exf_TextOnly; }
  /// \ru Следует ли компоненты экспортировать в разные файлы (если позволяет формат). \en Export components into separate files ( if provided in format). 
  virtual bool           ExportComponentsSeparately() const { return false; }
  /// \ru Получить ЛСК, относительно которой позиционирована модель. \en Get the location, the model is placed in.
  virtual MbPlacement3D  GetOriginLocation() const = 0;
  /// \ru Заменять ли принудительно СК компонент на правые. \en Replace components' placements to right-oriented.
  virtual bool           ReplaceLocationsToRight() const = 0;
  /**  \brief \ru Сшивать ли поверхности автоматически.
              \en If surfaces should be stitched automatically. \~
    \return \ru true - Сшивать поверхности автоматически, false - Спросить пользователя, сшивать ли поверхности.
            \en true - Stitch surfaces automatically, false - Ask user first time. \~
    \param[out] stitchPrecision - \ru Точность сшивки.
                                  \en Stitch precision. \~
  */
  virtual bool           EnableAutoStitch( double& /*stitchPrecision*/ ) const = 0;

  /**  \brief \ru Получить множитель единиц длины по отношению к миллиметру. 
              \en Get the factor of the length units to millimeters. \~
    \details \ru При импорте, если единицы измерения не заданы явно с помощью средств, предоставляемых обменным форматом,
                 все размеры (координаты точек, радиусы) умножаются на возвращаемое значение. При экспорте либо с помощью 
                 средств, предоставляемых обменным форматом, задаются единицы измерения, либо все размеры модели (координаты 
                 точек, радиусы) умножаются на возвращаемое значение.
             \en During the import all spatial objects (coordinate values, radiuses) are multiplied by the returned value, 
                 unless the scale factor comes from the exchange file. During the export the exchange format facilities are 
                 used to specify the length units or all spatial objects (coordinate values, radiuses) are multiplied by the 
                 returned value. \~
  */
  virtual double         LengthUnitsFactor() const { return LENGTH_UNIT_MM; } 


  /**  \brief \ru Получить дополнительный множитель единиц длины по отношению к миллиметру в модели приложения. 
  \en Get addifional factor of the length units to millimeters in the application model. \~
  \details \ru При импорте из всех форматов за исключением JT, если единицы измерения, в том числе и заданные 
  явно с помощью средств, предоставляемых обменным форматом, все размеры (координаты точек, радиусы) умножаются 
  на возвращаемое значение. При экспорте либо с помощью средств, предоставляемых обменным форматом, задаются 
  единицы измерения, либо все размеры модели (координаты точек, радиусы) умножаются на возвращаемое значение.
  \en During the import from all formats except for JT all spatial objects (coordinate values, radiuses) are 
  multiplied by the returned value, even if the scale factor comes from the exchange file. During the export the 
  exchange format facilities are used to specify the length units or all spatial objects (coordinate values, 
  radiuses) are multiplied by the returned value. \~
  */
  virtual double         AppLengthUnitsFactor() const { return LENGTH_UNIT_MM; } 

  /**  \brief \ru Сделать запись в журнал конвертирования.
              \en Make a record in the converter report. \~
    \param[in] id - \ru Идентификатор элемента внутри файла стороннего формата.
                    \en Identifier of an element inside the file of a foreign format. \~
    \param[in] msgType - \ru Тип сообщения.
                         \en Message type. \~
    \param[in] msgText - \ru Код сообщения.
                         \en Message code. \~
  */
  virtual void           LogReport( ptrdiff_t id, eMsgType msgType, eMsgDetail msgText ) = 0;

//   /**  \brief \ru Следует ли показывать сообщения и диалоги пользователю. \en Whether to show messages and dialog to the user. \~
//    \details \ru Обеспечивает работу через API. \en Provide possibility for work via API. \~
//    \return \ru true - обычная работа, false - через API. \en true - ordinary work, false - via API. \~
//   */
  virtual bool          CanShowMessages() const = 0;
  /// \ru Дать данные вычисления триангуляции (для конвертера JT, STL и VRML). \en Get data for step calculation during triangulation (for JT, STL, VRML only).
  virtual MbStepData    TesselationParameters() const { return MbStepData(); }
  /// \ru Дать данные вычисления триангуляции уровня детализации (для конвертера JT). \en Get data for step calculation during triangulation of LOD0 (for JTonly).
  virtual MbStepData    LOD0TesselationParameters() const { return TesselationParameters(); }
  /// \ru Флаг сохранения совпадающих точек швов. (для конвертера STL и VRML). \en Whether to keep coincident points of seams (for STL, VRML only).
  virtual bool          DualSeams() const { return true; }
  /// \ru Флаг сохранения совпадающих точек швов. (для конвертера STL и VRML). \en Whether to keep coincident points of seams (for STL, VRML only).
  virtual void          DualSeams( bool ) {}
  /// \ru Проводить ли аудит траснляции. \en Whether to audit the translation.
  virtual bool          TotalAudit() { return false; }

  /// \ru Выполнять ли слияние подобных граней. \en Whether to join similar faces.
  virtual bool          JoinSimilarFaces() const { return true; }
  /// \ru Добавлять ли удаленные грани в качестве оболочек. \en Whether to add removed faces as shells.
  virtual bool          AddRemovedFacesAsShells() const { return false; }
}; // IConvertorProperty3D


//------------------------------------------------------------------------------
/** \brief \ru Интерфейс конвертера.
           \en Converter's interface. \~
  \details \ru Интерфейс конвертера реализует методы экспорта модели в файлы обменных форматов
    и импорта из них.
           \en Converter's interface implements methods of export of the model to files of exchange formats
    and import from them. \~
*/
class IConvertor3D {
public:
  virtual ~IConvertor3D() {}
  
public:
  /** \brief \ru Прочитать файл формата SAT.
             \en Read a file of SAT format. \~
  \details \ru Прочитать файл формата SAT или указанный поток. 
    Если задан поток, то запись производится в присланный поток. 
    Если поток не задан (нулевой), то открывается поток для файла, заданного в свойствах конвертера. \n
           \en Read a file of SAT format or a specified stream. 
    If a stream is specified, then the record is performed to the given stream. 
    If a stream is not specified (null), then a stream is being opened for file specified in the properties of the converter. \n \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] stream - \ru Поток, из которого производится чтение (может быть NULL).
                      \en Stream from which reading is performed (can be NULL). \~
  \param[in] indicator - \ru Индикатор хода процесса (может быть NULL).
                         \en The process progress indicator (can be NULL). \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей.
                           \en Dialog of request for stitching the surfaces. \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup ACIS_Exchange
  */
  virtual MbeConvResType SATRead  ( IConvertorProperty3D & prop, ItModelDocument & idoc, std::iostream * stream, IProgressIndicator * indicator, MbRefItem * qeuryStitch ) = 0;

  /** \brief \ru Записать файл формата SAT.
             \en Write file of SAT format. \~
  \details \ru Записать файл формата SAT или указанный поток. 
    Если задан поток, то запись производится в присланный поток. 
    Если поток не задан (нулевой), то открывается поток для файла, заданного в свойствах конвертера. \n
           \en Write file of SAT format or the specified stream. 
    If a stream is specified, then the record is performed to the given stream. 
    If a stream is not specified (null), then a stream is being opened for file specified in the properties of the converter. \n \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] stream - \ru Поток, в который производится запись (может быть NULL).
                      \en Stream in which the record is performed (can be NULL). \~
  \param[in] indicator - \ru Индикатор хода процесса (может быть NULL).
                         \en The process progress indicator (can be NULL). \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup ACIS_Exchange
  */
  virtual MbeConvResType SATWrite ( IConvertorProperty3D & prop, ItModelDocument & idoc, std::iostream * stream, IProgressIndicator * indicator ) = 0;

  /** \brief \ru Прочитать файл формата SAT.
             \en Read a file of SAT format. \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей.
                           \en Dialog of request for stitching the surfaces. \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup ACIS_Exchange
  */
  virtual MbeConvResType SATRead  ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0, MbRefItem * qeuryStitch = 0 ) = 0;

  /** \brief \ru Записать файл формата SAT.
             \en Write file of SAT format. \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей (не используется).
                           \en Dialog of request for stitching the surfaces (not used). \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup ACIS_Exchange
  */
  virtual MbeConvResType SATWrite ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0, MbRefItem * qeuryStitch = 0 ) = 0;

  /** \brief \ru Прочитать файл формата IGES.
             \en Read a file of IGES format. \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей.
                           \en Dialog of request for stitching the surfaces. \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup IGES_Exchange
  */
  virtual MbeConvResType IGSRead  ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0, MbRefItem * qeuryStitch = 0 ) = 0;

  /** \brief \ru Записать файл формата IGES.
             \en Write a file of IGES format. \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей (не используется).
                           \en Dialog of request for stitching the surfaces (not used). \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup IGES_Exchange
  */
  virtual MbeConvResType IGSWrite ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0, MbRefItem * qeuryStitch = 0 ) = 0;

  /** \brief \ru Прочитать файл формата JT.
             \en Read a file of JT format. \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей.
                           \en Dialog of request for stitching the surfaces. \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup IGES_Exchange
  */
  virtual MbeConvResType JTRead  ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0, MbRefItem * qeuryStitch = 0 ) = 0;

  /** \brief \ru Записать файл формата JT.
             \en Write a file of JT format. \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей (не используется).
                           \en Dialog of request for stitching the surfaces (not used). \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup IGES_Exchange
  */
  virtual MbeConvResType JTWrite ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0, MbRefItem * qeuryStitch = 0 ) = 0;

  /** \brief \ru Прочитать файл формата Parasolid.
             \en Read a file of Parasolid format. \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей.
                           \en Dialog of request for stitching the surfaces. \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup Parasolid_Exchange
  */
  virtual MbeConvResType XTRead   ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0, MbRefItem * qeuryStitch = 0 ) = 0;

  /** \brief \ru Записать файл формата Parasolid.
             \en Write a file of Parasolid format. \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей.
                           \en Dialog of request for stitching the surfaces. \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup Parasolid_Exchange
  */
  virtual MbeConvResType XTWrite  ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0, MbRefItem * qeuryStitch = 0 ) = 0;

  /** \brief \ru Прочитать файл формата STEP.
             \en Read a file of STEP format. \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей (не используется).
                           \en Dialog of request for stitching the surfaces (not used). \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup STEP_Exchange
  */
  virtual MbeConvResType STEPRead ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0, MbRefItem * qeuryStitch = 0 ) = 0;

  /** \brief \ru Записать файл формата STEP.
             \en Write a file of STEP format. \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей (не используется).
                           \en Dialog of request for stitching the surfaces (not used). \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup STEP_Exchange
  */
  virtual MbeConvResType STEPWrite( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0, MbRefItem * qeuryStitch = 0 ) = 0;
  
  /** \brief \ru Прочитать файл формата STL.
             \en Read a file of STL format. \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей (не используется).
                           \en Dialog of request for stitching the surfaces (not used). \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup STL_Exchange
  */
  virtual MbeConvResType STLRead ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0, MbRefItem * qeuryStitch = 0 ) = 0;

  /** \brief \ru Записать файл формата STL.
             \en Write a file of STL format. \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей (не используется).
                           \en Dialog of request for stitching the surfaces (not used). \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup STL_Exchange
  */
  virtual MbeConvResType STLWrite ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0, MbRefItem * qeuryStitch = 0 ) = 0;

  /** \brief \ru Прочитать файл формата VRML.
             \en Read a file of VRML format. \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей (не используется).
                           \en Dialog of request for stitching the surfaces (not used). \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup VRML_Exchange
  */
  virtual MbeConvResType VRMLRead ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0, MbRefItem * qeuryStitch = 0 ) = 0;

  /** \brief \ru Записать файл формата VRML.
             \en Write a file of VRML format. \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей (не используется).
                           \en Dialog of request for stitching the surfaces (not used). \~
  \param[in] devSag - \ru Угловой шаг для расчёта триангуляционной сетки.
                      \en Deviate sag requiref for grid calculateion. \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup VRML_Exchange
  */
  virtual MbeConvResType VRMLWrite( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0, MbRefItem * qeuryStitch = 0 ) = 0;

  /** \brief \ru Прочитать файл формата GRDECL.
             \en Read a file of GRDECL format. \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей (не используется).
                           \en Dialog of request for stitching the surfaces (not used). \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup VRML_Exchange
  */
  virtual MbeConvResType GRDECLRead ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0, MbRefItem * qeuryStitch = 0 ) = 0;

  /** \brief \ru Записать файл формата GRDECL.
             \en Write a file of GRDECL format. \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей (не используется).
                           \en Dialog of request for stitching the surfaces (not used). \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup STL_Exchange
  */
  virtual MbeConvResType GRDECLWrite ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0, MbRefItem * qeuryStitch = 0 ) = 0;

  /** \brief \ru Прочитать файл с облаком точек в формате ASCII.
              \en Read a file of ASCII Point Cloud format. \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей (не используется).
                           \en Dialog of request for stitching the surfaces (not used). \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup ASCII_Exchange
  */
  virtual MbeConvResType ASCIIPointCloudRead ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0, MbRefItem * qeuryStitch = 0 ) = 0;

  /** \brief \ru Записать файл с облаком точек в формате ASCII..
             \en Write a point cloud file of ASCII format. \~
  \param[in] prop - \ru Реализация интерфейса свойств конвертера.
                    \en Implementation of converter's properties interface. \~
  \param[in] idoc - \ru Реализация интерфейса документа.
                    \en Implementation of document interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \param[in] qeuryStitch - \ru Диалог запроса на сшивку поверхностей (не используется).
                           \en Dialog of request for stitching the surfaces (not used). \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup ASCII_Exchange
  */
  virtual MbeConvResType ASCIIPointCloudWrite ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0, MbRefItem * qeuryStitch = 0 ) = 0;

}; // IConvertor3D


//------------------------------------------------------------------------------
/** \brief \ru Получить интерфейс конвертера.
           \en Get the converter interface. \~
\ingroup Exchange_Interface
*/
CONV_FUNC (IConvertor3D *) GetConvertor3D();



/** \brief \ru Прочитать файл формата SAT.
            \en Read a file of SAT format. \~
\param[in] prop - \ru Реализация интерфейса свойств конвертера.
                  \en Implementation of converter's properties interface. \~
\param[in] idoc - \ru Реализация интерфейса документа.
                  \en Implementation of document interface. \~
\param[in] indicator - \ru Индикатор хода процесса.
                        \en The process progress indicator. \~
\return \ru Код завершения операции.
        \en Code of the operation termination. \~
\ingroup ACIS_Exchange
*/
CONV_FUNC (MbeConvResType ) SATRead ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator );

/** \brief \ru Записать файл формата SAT.
            \en Write file of SAT format. \~
\details \ru Записать файл формата SAT или указанный поток. 
  Если задан поток, то запись производится в присланный поток. 
  Если поток не задан (нулевой), то открывается поток для файла, заданного в свойствах конвертера. \n
          \en Write file of SAT format or the specified stream. 
  If a stream is specified, then the record is performed to the given stream. 
  If a stream is not specified (null), then a stream is being opened for file specified in the properties of the converter. \n \~
\param[in] prop - \ru Реализация интерфейса свойств конвертера.
                  \en Implementation of converter's properties interface. \~
\param[in] idoc - \ru Реализация интерфейса документа.
                  \en Implementation of document interface. \~
\param[in] indicator - \ru Индикатор хода процесса (может быть NULL).
                        \en The process progress indicator (can be NULL). \~
\return \ru Код завершения операции.
        \en Code of the operation termination. \~
\ingroup ACIS_Exchange
*/
CONV_FUNC (MbeConvResType ) SATWrite ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator );
/** \brief \ru Прочитать файл формата IGES.
            \en Read a file of IGES format. \~
\param[in] prop - \ru Реализация интерфейса свойств конвертера.
                  \en Implementation of converter's properties interface. \~
\param[in] idoc - \ru Реализация интерфейса документа.
                  \en Implementation of document interface. \~
\param[in] indicator - \ru Индикатор хода процесса.
                        \en The process progress indicator. \~
\return \ru Код завершения операции.
        \en Code of the operation termination. \~
\ingroup IGES_Exchange
*/
CONV_FUNC (MbeConvResType ) IGSRead ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0 );

/** \brief \ru Записать файл формата IGES.
            \en Write a file of IGES format. \~
\param[in] prop - \ru Реализация интерфейса свойств конвертера.
                  \en Implementation of converter's properties interface. \~
\param[in] idoc - \ru Реализация интерфейса документа.
                  \en Implementation of document interface. \~
\param[in] indicator - \ru Индикатор хода процесса.
                        \en The process progress indicator. \~
\return \ru Код завершения операции.
        \en Code of the operation termination. \~
\ingroup IGES_Exchange
*/
CONV_FUNC (MbeConvResType ) IGSWrite ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0 );

/** \brief \ru Прочитать файл формата JT.
            \en Read a file of JT format. \~
\param[in] prop - \ru Реализация интерфейса свойств конвертера.
                  \en Implementation of converter's properties interface. \~
\param[in] idoc - \ru Реализация интерфейса документа.
                  \en Implementation of document interface. \~
\param[in] indicator - \ru Индикатор хода процесса.
                        \en The process progress indicator. \~
\return \ru Код завершения операции.
        \en Code of the operation termination. \~
\ingroup IGES_Exchange
*/
CONV_FUNC (MbeConvResType ) JTRead ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0 );

/** \brief \ru Записать файл формата JT.
            \en Write a file of JT format. \~
\param[in] prop - \ru Реализация интерфейса свойств конвертера.
                  \en Implementation of converter's properties interface. \~
\param[in] idoc - \ru Реализация интерфейса документа.
                  \en Implementation of document interface. \~
\param[in] indicator - \ru Индикатор хода процесса.
                        \en The process progress indicator. \~
\return \ru Код завершения операции.
        \en Code of the operation termination. \~
\ingroup IGES_Exchange
*/
CONV_FUNC (MbeConvResType ) JTWrite ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0 );

/** \brief \ru Прочитать файл формата Parasolid.
            \en Read a file of Parasolid format. \~
\param[in] prop - \ru Реализация интерфейса свойств конвертера.
                  \en Implementation of converter's properties interface. \~
\param[in] idoc - \ru Реализация интерфейса документа.
                  \en Implementation of document interface. \~
\param[in] indicator - \ru Индикатор хода процесса.
                        \en The process progress indicator. \~\~
\return \ru Код завершения операции.
        \en Code of the operation termination. \~
\ingroup Parasolid_Exchange
*/
CONV_FUNC (MbeConvResType ) XTRead ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0 );

/** \brief \ru Записать файл формата Parasolid.
            \en Write a file of Parasolid format. \~
\param[in] prop - \ru Реализация интерфейса свойств конвертера.
                  \en Implementation of converter's properties interface. \~
\param[in] idoc - \ru Реализация интерфейса документа.
                  \en Implementation of document interface. \~
\param[in] indicator - \ru Индикатор хода процесса.
                        \en The process progress indicator. \~
\return \ru Код завершения операции.
        \en Code of the operation termination. \~
\ingroup Parasolid_Exchange
*/
CONV_FUNC (MbeConvResType ) XTWrite ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0 );

/** \brief \ru Прочитать файл формата STEP.
            \en Read a file of STEP format. \~
\param[in] prop - \ru Реализация интерфейса свойств конвертера.
                  \en Implementation of converter's properties interface. \~
\param[in] idoc - \ru Реализация интерфейса документа.
                  \en Implementation of document interface. \~
\param[in] indicator - \ru Индикатор хода процесса.
                        \en The process progress indicator. \~
\return \ru Код завершения операции.
        \en Code of the operation termination. \~
\ingroup STEP_Exchange
*/
CONV_FUNC (MbeConvResType ) STEPRead ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0 );

/** \brief \ru Записать файл формата STEP.
            \en Write a file of STEP format. \~
\param[in] prop - \ru Реализация интерфейса свойств конвертера.
                  \en Implementation of converter's properties interface. \~
\param[in] idoc - \ru Реализация интерфейса документа.
                  \en Implementation of document interface. \~
\param[in] indicator - \ru Индикатор хода процесса.
                        \en The process progress indicator. \~
\return \ru Код завершения операции.
        \en Code of the operation termination. \~
\ingroup STEP_Exchange
*/
CONV_FUNC (MbeConvResType ) STEPWrite( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0 );
  
/** \brief \ru Прочитать файл формата STL.
            \en Read a file of STL format. \~
\param[in] prop - \ru Реализация интерфейса свойств конвертера.
                  \en Implementation of converter's properties interface. \~
\param[in] idoc - \ru Реализация интерфейса документа.
                  \en Implementation of document interface. \~
\param[in] indicator - \ru Индикатор хода процесса.
                        \en The process progress indicator. \~
\return \ru Код завершения операции.
        \en Code of the operation termination. \~
\ingroup STL_Exchange
*/
CONV_FUNC (MbeConvResType ) STLRead ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0 );

/** \brief \ru Записать файл формата STL.
            \en Write a file of STL format. \~
\param[in] prop - \ru Реализация интерфейса свойств конвертера.
                  \en Implementation of converter's properties interface. \~
\param[in] idoc - \ru Реализация интерфейса документа.
                  \en Implementation of document interface. \~
\param[in] indicator - \ru Индикатор хода процесса.
                        \en The process progress indicator. \~
\return \ru Код завершения операции.
        \en Code of the operation termination. \~
\ingroup STL_Exchange
*/
CONV_FUNC (MbeConvResType ) STLWrite ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0 );

/** \brief \ru Прочитать файл формата VRML.
            \en Read a file of VRML format. \~
\param[in] prop - \ru Реализация интерфейса свойств конвертера.
                  \en Implementation of converter's properties interface. \~
\param[in] idoc - \ru Реализация интерфейса документа.
                  \en Implementation of document interface. \~
\param[in] indicator - \ru Индикатор хода процесса.
                        \en The process progress indicator. \~
\return \ru Код завершения операции.
        \en Code of the operation termination. \~
\ingroup VRML_Exchange
*/
CONV_FUNC (MbeConvResType ) VRMLRead ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0 );

/** \brief \ru Прочитать файл формата GRDECL.
            \en Read a file of GRDECL format. \~
\param[in] prop - \ru Реализация интерфейса свойств конвертера.
                  \en Implementation of converter's properties interface. \~
\param[in] idoc - \ru Реализация интерфейса документа.
                  \en Implementation of document interface. \~
\param[in] indicator - \ru Индикатор хода процесса.
                        \en The process progress indicator. \~
\return \ru Код завершения операции.
        \en Code of the operation termination. \~
\ingroup VRML_Exchange
*/
CONV_FUNC (MbeConvResType ) GRDECLRead ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0 );

/** \brief \ru Записать файл формата GRDECL.
            \en Write a file of GRDECL format. \~
\param[in] prop - \ru Реализация интерфейса свойств конвертера.
                  \en Implementation of converter's properties interface. \~
\param[in] idoc - \ru Реализация интерфейса документа.
                  \en Implementation of document interface. \~
\param[in] indicator - \ru Индикатор хода процесса.
                        \en The process progress indicator. \~
\return \ru Код завершения операции.
        \en Code of the operation termination. \~
\ingroup STL_Exchange
*/
CONV_FUNC (MbeConvResType ) GRDECLWrite ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0 );

/** \brief \ru Записать файл формата VRML.
            \en Write a file of VRML format. \~
\param[in] prop - \ru Реализация интерфейса свойств конвертера.
                  \en Implementation of converter's properties interface. \~
\param[in] idoc - \ru Реализация интерфейса документа.
                  \en Implementation of document interface. \~
\param[in] indicator - \ru Индикатор хода процесса.
                        \en The process progress indicator. \~
\return \ru Код завершения операции.
        \en Code of the operation termination. \~
\ingroup VRML_Exchange
*/
CONV_FUNC (MbeConvResType ) VRMLWrite( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0 );


/** \brief \ru Прочитать файл с облаком точек в формате ASCII.
           \en Read a file of ASCII Point Cloud format. \~
\param[in] prop - \ru Реализация интерфейса свойств конвертера.
                  \en Implementation of converter's properties interface. \~
\param[in] idoc - \ru Реализация интерфейса документа.
                  \en Implementation of document interface. \~
\param[in] indicator - \ru Индикатор хода процесса.
                       \en The process progress indicator. \~
\return \ru Код завершения операции.
        \en Code of the operation termination. \~
\ingroup ASCII_Exchange
*/
CONV_FUNC (MbeConvResType ) ASCIIPointCloudRead ( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0 );


/** \brief \ru Записать файл с облаком точек в формате ASCII..
           \en Write a point cloud file of ASCII format. \~
\param[in] prop - \ru Реализация интерфейса свойств конвертера.
                  \en Implementation of converter's properties interface. \~
\param[in] idoc - \ru Реализация интерфейса документа.
                  \en Implementation of document interface. \~
\param[in] indicator - \ru Индикатор хода процесса.
                       \en The process progress indicator. \~
\return \ru Код завершения операции.
        \en Code of the operation termination. \~
\ingroup ASCII_Exchange
*/
CONV_FUNC (MbeConvResType ) ASCIIPointCloudWrite( IConvertorProperty3D & prop, ItModelDocument & idoc, IProgressIndicator * indicator = 0 );


namespace c3d {
  
  /** \brief \ru Прочитать файл обменного формата в модель.
             \en Read a file of an exchange format into model. \~
  \details \ru Если свойства конвертера заданы, аргумент fileName игнорируется, а имя файла берётся из свойств конвертера.
  В противном случае импорт идёт с умолчательными параметрами, соответствующими реализации ConvConvertorProperty3D. \~
  \en The fileName argument is not used if converter properties are defined obviously, file path comes from the FullFilePath 
  method. Otherwise default parameters corresponding ConvConvertorProperty3D implementation are used for import.
  \param[out] model -    \ru Модель.
                         \en The model. \~
  \param[in] filePath -  \ru Путь файла.
                         \en File path. \~
  \param[in] prop -      \ru Реализация интерфейса свойств конвертера.
                         \en Implementation of converter's properties interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup Exchange_Interface
  */
  CONV_FUNC (MbeConvResType) ImportFromFile(       MbModel &              model, 
                                             const path_string &          fileName, 
                                                   IConvertorProperty3D * prop = 0,
                                                   IProgressIndicator *   indicator = 0 );

  /** \brief \ru Прочитать файл обменного формата в модель.
  \en Read a file of an exchange format into model. \~
  \details \ru Если свойства конвертера заданы, аргумент fileName игнорируется, а имя файла берётся из свойств конвертера.
  В противном случае импорт идёт с умолчательными параметрами, соответствующими реализации ConvConvertorProperty3D. \~
  \en The fileName argument is not used if converter properties are defined obviously, file path comes from the FullFilePath 
  method. Otherwise default parameters corresponding ConvConvertorProperty3D implementation are used for import.
  \param[out] mDoc -     \ru Модельный документ.
                         \en The model. \~
  \param[in] filePath -  \ru Путь файла.
                         \en File path. \~
  \param[in] prop -      \ru Реализация интерфейса свойств конвертера.
                         \en Implementation of converter's properties interface. \~
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup Exchange_Interface
  */
  CONV_FUNC (MbeConvResType) ImportFromFile(       ItModelDocument &      mDoc, 
                                             const path_string &          filePath, 
                                                   IConvertorProperty3D * prop, 
                                                   IProgressIndicator *   indicator );

  /** \brief \ru Записать модель в файл обменного формата.
             \en Write the model into an exchange format file. \~
  \details \ru Если свойства конвертера заданы, аргумент fileName игнорируется, а имя файла берётся из свойств конвертера.
  В противном случае экспорт идёт с умолчательными параметрами, соответствующими реализации ConvConvertorProperty3D. \~
           \en The fileName argument is not used if converter properties are defined obviously, file path comes from the FullFilePath 
  method. Otherwise default parameters corresponding ConvConvertorProperty3D implementation are used for export.
  \param[out] model -    \ru Модель.
                         \en The model. \~
  \param[in] filePath -  \ru Путь файла.
                         \en File path. \~
  \param[in] prop -      \ru Реализация интерфейса свойств конвертера.
                         \en Implementation of converter's properties interface. \~  
  \param[in] indicator - \ru Индикатор хода процесса.
                         \en The process progress indicator. \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup Exchange_Interface
  */
  CONV_FUNC (MbeConvResType) ExportIntoFile(       MbModel &              model, 
                                             const path_string &          filePath, 
                                                   IConvertorProperty3D * prop = 0, 
                                                   IProgressIndicator *   indicator = 0 );

  /** \brief \ru Импортировать данные из буфера в модель.
              \en Import data from buffer into model. \~
  \param[out] model -      \ru Модель.
                           \en The model. \~
  \param[in] data -        \ru Буфер.
                           \en Buffer. \~
  \param[in] length -      \ru Размер буфера.
                           \en Buffer size. \~
  \param[in] modelFormat - \ru Формат модели.
                           \en Model format. \~
  \param[in] prop -        \ru Реализация интерфейса свойств конвертера.
                           \en Implementation of converter's properties interface. \~
  \param[in] indicator -   \ru Индикатор хода процесса.
                           \en The process progress indicator. \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup Exchange_Interface
  */
  CONV_FUNC (MbeConvResType) ImportFromBuffer(       MbModel &              model, 
                                               const char *                 data, 
                                                     size_t                 length, 
                                                     MbeModelExchangeFormat modelFormat, 
                                                     IConvertorProperty3D * prop = 0, 
                                                     IProgressIndicator *   indicator = 0 );

  /** \brief \ru Экспортировать модель в буфер.
             \en Export model into buffer. \~
  \param[in] model -       \ru Модель.
                           \en The model. \~
  \param[in] modelFormat - \ru Формат модели.
                           \en Model format. \~
  \param[out] data -       \ru Буфер.
                           \en Buffer. \~
  \param[out] length -     \ru Размер буфера.
                           \en Buffer size. \~  
  \param[in] prop -        \ru Реализация интерфейса свойств конвертера.
                           \en Implementation of converter's properties interface. \~
  \param[in] indicator -   \ru Индикатор хода процесса.
                           \en The process progress indicator. \~
  \return \ru Код завершения операции.
          \en Code of the operation termination. \~
  \ingroup Exchange_Interface
  */
  CONV_FUNC (MbeConvResType) ExportIntoBuffer( MbModel &              model, 
                                               MbeModelExchangeFormat modelFormat, 
                                               char *&                data, 
                                               size_t &               length, 
                                               IConvertorProperty3D * prop = 0, 
                                               IProgressIndicator *   indicator = 0 );
};


/** \} */


#endif // __CONV_I_CONVERTER_H
