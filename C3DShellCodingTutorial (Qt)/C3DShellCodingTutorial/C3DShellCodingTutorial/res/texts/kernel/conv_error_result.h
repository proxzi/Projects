////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief  \ru Перечисления, используемые при импорте и экспорте.
          \en Enumerations for import/export operations.\~
  \details  \ru Определены перечисления, определяющие результат конвертирования,
 разрешение на чтение и запись различных объектов и передаваемых черезх конвертер строк.
            \en Converting result, objects and properties filters, special strings 
 of enumerations are defined.\~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CONV_ERROR_RESULT_H
#define __CONV_ERROR_RESULT_H


#include <mb_enum.h>


//------------------------------------------------------------------------------
/** \brief  \ru Константы единиц измерения. 
            \en Length units constants.\~   
\ingroup Data_Interface
*/
// ---
/// \ru Миллиметры. \en Millimeters.
#define LENGTH_UNIT_MM 1.0
/// \ru Сантиметры. \en Centimeters.
#define LENGTH_UNIT_CM 10.0
/// \ru Дециметры. \en Decimeters.
#define LENGTH_UNIT_DM 100.0
/// \ru Метры. \en Meters.
#define LENGTH_UNIT_METER 1000.0
/// \ru Дюймы. \en Inches.
#define LENGTH_UNIT_INCH 25.4


//------------------------------------------------------------------------------
/** \brief  \ru Прикладной протокол. 
            \en Applied protocol.\~   
\ingroup Data_Interface
*/
// ---
enum MbeImpExpFormat {
  ief_STEP203,  ///< \ru STEP прикладной протокол 203 ( Проектирование с управляемой конфигурацией ).  \en STEP applied protocol STEP 203 (Configuration controlled design).
  ief_STEP214,  ///< \ru STEP прикладной протокол 214 ( Проектирование автомобилей ).                  \en STEP applied protocol STEP 214 (Automotive design).
  ief_STEP242,  ///< \ru STEP прикладной протокол 242 ( Проектирование автомобилей ).                  \en STEP applied protocol STEP 242 (Automotive design).  
};


#define EXPORT_DEFAULT  -1  ///< \ru По умолчанию для заданного формата.                                           \en Default for specified format.
#define EXPORT_STEP_203 203 ///< \ru STEP прикладной протокол 203 ( Проектирование с управляемой конфигурацией ).  \en STEP applied protocol STEP 203 (Configuration controlled design).
#define EXPORT_STEP_214 214 ///< \ru STEP прикладной протокол 214 ( Проектирование автомобилей ).                  \en STEP applied protocol STEP 214 (Automotive design).
#define EXPORT_STEP_242 242 ///< \ru STEP прикладной протокол 242.                                                 \en STEP applied protocol STEP 242.  
#define EXPORT_ACIS_4   4   ///< \ru ACIS версия 4.0.                                                              \en ACIS version 4.0.  
#define EXPORT_ACIS_7   7   ///< \ru ACIS версия 7.0 (по умолчанию).                                               \en ACIS version 7.0 (default).  
#define EXPORT_ACIS_10  10  ///< \ru ACIS версия 10.0.                                                             \en ACIS version 10.0.  


//------------------------------------------------------------------------------
/** \brief  \ru Обменный формат модели. 
            \en Model exchange format.\~   
\ingroup Data_Interface
*/
// ---
enum MbeModelExchangeFormat {
  mxf_autodetect, ///< \ru Интерпретировать содержимое по расширению файла.                                                    \en File extension defines format.
  mxf_ACIS,       ///< \ru Интерпретировать содержимое как ACIS (.sat).                                                        \en Read data from buffer as ACIS (.sat).
  mxf_IGES,       ///< \ru Интерпретировать содержимое как IGES (.igs или .iges).                                              \en Read data from buffer as IGES (.igs or .iges).
  mxf_JT,         ///< \ru Интерпретировать содержимое как JT (.jt).                                                           \en Read data from buffer as JT (.jt).
  mxf_Parasolid,  ///< \ru Интерпретировать содержимое как Parasolid (.x_t, .x_b, .xmt_txt, .xmp_txt, .xmt_bin или .xmp_bin ). \en Read data from buffer as Parasolid (.x_t, .x_b, .xmt_txt, .xmp_txt, .xmt_bin or .xmp_bin ).
  mxf_STEP,       ///< \ru Интерпретировать содержимое как STEP (.stp или .step).                                              \en Read data from buffer as STEP (.stp or .step).
  mxf_STL,        ///< \ru Интерпретировать содержимое как STL (.stl).                                                         \en Read data from buffer as STL (.stl).
  mxf_VRML,       ///< \ru Интерпретировать содержимое как VRML (.wrl).                                                        \en Read data from buffer as VRML (.wrl).
  mxf_GRDECL,     ///< \ru Интерпретировать содержимое как GRDECL (.grdecl).                                                   \en Read data from buffer as GRDECL (.grdecl).
  mxf_ASCIIPoint, ///< \ru Интерпретировать содержимое как облако точек в ASCII (.txt, .asc или .xyz).                         \en Read data from buffer as ASCII point cloud (.txt, .asc or .xyz).
  mxf_C3D,        ///< \ru Интерпретировать содержимое как C3D (.c3d).                                                         \en Read data from buffer as C3D (.c3d).
};


//------------------------------------------------------------------------------
/** \brief  \ru Результат конвертирования. 
            \en Result of converting operation.
\ingroup Data_Interface
*/
// ---
enum MbeConvResType {
  cnv_Success = 0,           ///< \ru Успешное завершение.                 \en Success.
  cnv_Error,                 ///< \ru Ошибка в процессе конвертирования.   \en Error.
  cnv_UserCanceled,          ///< \ru Процесс прерван пользователем.       \en Process interrupted by user.
  cnv_NoBody,                ///< \ru Не найдено тел.                      \en No solids found.
  cnv_NoObjects,             ///< \ru Не найдено объектов.                 \en No objects found.
  cnv_FileOpenError,         ///< \ru Ошибка открытия файла.               \en File open error.
  cnv_FileWriteError,        ///< \ru Ошибка записи файла.                 \en File write error.
  cnv_FileDeleteError,       ///< \ru Ошибка удаления файла.               \en Could not delete file.
  cnv_ImpossibleReadAssembly,///< \ru Не поддерживает работу со сборками.  \en Assemblies are not supported.
  cnv_LicenseNotFound,       ///< \ru Ошибка получения лицензии.           \en License check failure.
  cnv_NotEnoughMemory,       ///< \ru Недостаточно памяти.                 \en Not enough memory.
  cnv_UnknownExtension       ///< \ru Неизвестное расширение файла.        \en Unknown file extenstion.
};


//------------------------------------------------------------------------------
/** \brief  \ru Индексы, управляющие разрешением на чтение или запись объектов.
            \en Indeces, which filter imported/exported objects or properties.\~   
\ingroup Data_Interface
*/
// ---
enum MbeIOPermiss {
  iop_rSolid = 0,       ///< \ru Разрешение на чтение твёрдых тел.  \en Import solid solids.
  iop_wSolid,           ///< \ru Разрешение на запись твёрдых тел.  \en Export solid solids.
  iop_rSurface,         ///< \ru Разрешение на чтение поверхностей. \en Import surfaces.
  iop_wSurface,         ///< \ru Разрешение на запись поверхностей. \en Export surfaces.
  iop_rCurve,           ///< \ru Разрешение на чтение кривых.       \en Import curves.
  iop_wCurve,           ///< \ru Разрешение на запись кривых.       \en Export curves.
  iop_rDrafts,          ///< \ru Разрешение на чтение эскизов (не применяется).       \en Import drafts (ignored).
  iop_wDrafts,          ///< \ru Разрешение на запись эскизов.       \en Export drafts.
  iop_rInvisible,       ///< \ru Разрешение на чтение невидимых объектов (не применяется).  \en Import invisible objects (not applied).
  iop_wInvisible,       ///< \ru Разрешение на запись невидимых объектов.  \en Export invisible objects.
  iop_rPoint,           ///< \ru Разрешение на чтение точек.        \en Import points.
  iop_wPoint,           ///< \ru Разрешение на запись точек.        \en Export points.
  iop_rDocInfo,         ///< \ru Разрешение на чтение информации о документе (автор, организация, комментарии).  \en Import components info ( author, organization, description ).
  iop_wDocInfo,         ///< \ru Разрешение на запись информации о документе (автор, организация, комментарии).  \en Export components info ( author, organization, description ).
  iop_rTextDescription, ///< \ru Разрешение на чтение технических требований.  \en Import technical requirements.
  iop_wTextDescription, ///< \ru Разрешение на запись технических требований.  \en Export technical requirements.
  iop_rDimensions,      ///< \ru Разрешение на чтение размеров.     \en Import dimensions.
  iop_wDimensions,      ///< \ru Разрешение на запись размеров.     \en Export dimensions.
  iop_rAttributes,      ///< \ru Разрешение на чтение атрибутов.     \en Import attributes.
  iop_wAttributes,      ///< \ru Разрешение на запись атрибутов.     \en Export attributes.
  iop_rBRep,            ///< \ru Разрешение на чтение форм изделий в граничном представлении (только в JT).  \en Import shapes in boundary representation (JT only).
  iop_wBRep,            ///< \ru Разрешение на запись форм изделий в граничном представлении (только в JT).  \en Export shapes in boundary representation (JT only).
  iop_rPolygonal,       ///< \ru Разрешение на чтение полигональных форм изделий.  \en Import polygonal shapes.
  iop_wPolygonal,       ///< \ru Разрешение на запись полигональных форм изделий.  \en Export polygonal shapes.
  iop_rLOD0,            ///< \ru Разрешение на чтение полигональных форм изделий уровня детализации 0.  \en Import polygonal shapes of the 0-th LOD.
  iop_wLOD0,            ///< \ru Разрешение на запись полигональных форм изделий уровня детализации 0.  \en Export polygonal shapes of the 0-th LOD.
  iop_rAssociated,      ///< \ru Разрешение на чтение ассоциированной геометрии (резьбы и др).  \en Import associated geometry (threads etc).
  iop_wAssociated,      ///< \ru Разрешение на запись ассоциированной геометрии (резьбы и др).  \en Export associated geometry (threads etc).
  iop_rDensity,         ///< \ru Разрешение на чтение единиц плотности.  \en Import density units.
  iop_wDensity,         ///< \ru Разрешение на запись единиц плотности.  \en Export density units.
  iop_rStyle,           ///< \ru Разрешение на чтение элементов оформления (цвет, начертание, и т.п.).  \en Import appearance.
  iop_wStyle,            ///< \ru Разрешение на запись элементов оформления (цвет, начертание, и т.п.).  \en Export appearance.
  iop_END
};


//------------------------------------------------------------------------------
/** \brief  \ru Индексы строк, передаваемых через конвертер.
            \en Indeхes of strings, transmitted through converter.\~   
\ingroup Data_Interface
*/
// ---
enum MbeConverterStrings {
   cvs_BEGIN = 0,        ///< \ru Для удобства перебора.           \en For lookup only.
   cvs_STEPAuthor,       ///< \ru Автор для конвертера STEP.       \en Author of the document, in STEP.
   cvs_STEPOrganization, ///< \ru Организация для конвертера STEP. \en The organization, the author is related with, in STEP.
   cvs_STEPComment,      ///< \ru Комментарий файла формата STEP.  \en Annotation, in STEP.
   cvs_END               ///< \ru Для удобства перебора.           \en For lookup only.
};


//------------------------------------------------------------------------------
/** \brief  \ru Ключи строк, соответствующих названию специальных атрибутов.
            \en Keys of the strings, which mark special attributes.\~   
\ingroup Data_Interface
*/
// ---
enum ePromtAttributeKey {
  pac_GConverterInternalIsDummy, ///< \ru Является ли элемент пустышкой.\~   
  pac_GeneralIsAssembly,         ///< \ru Является ли элемент сборкой. \en Is item assembly.\~   
  pac_GeneralFileName,           ///< \ru Имя файла. \en File name.\~   
  pac_STEPHeader,                ///< \ru Заголовок STEP. \en STEP header.\~   
  pac_STEPProduct,               ///< \ru Изделие STEP. \en STEP product.\~   
  pac_STEPPersonOrganization,    ///< \ru Лицо и организация STEP. \en STEP person and organization.\~   
  pac_STEPAssignedRole           ///< \ru Назначенная роль STEP. \en The role, assigned to the person.\~   
};


//------------------------------------------------------------------------------
/** \brief  \ru Представление текста при экспорте.
            \en Representation of exported text.\~   
\ingroup Data_Exchange
*/
// ---
enum eTextForm { 
  exf_TextOnly,     ///< \ru Только текст.      \en Text only.
  exf_GeometryOnly, ///< \ru Только геометрия.  \en Geometry only.
};


//------------------------------------------------------------------------------
/** \brief  \ru Тип сообщения об ошибке при выводе в лог.
            \en Type of a log message.\~   
\ingroup Data_Exchange
*/
// ---
enum eMsgType { 
  emt_ErrorNoId,///< \ru Ошибка формата. Значение id игнорируется, выводится только текст.  \en Error not related with a certain record. The id field is ignored.
  emt_TextOnly, ///< \ru Значение id игнорируется, выводится только текст.                  \en Used to type message only. The id field is ignored.
  emt_Info,     ///< \ru Рабочая информация.                                                \en Info.
  emt_Warning,  ///< \ru Предупреждение.                                                    \en Warning.
  emt_Error     ///< \ru Ошибка формата или неустранимая ошибка преобразования.             \en Format mismatch or fatal converting error.
};


//------------------------------------------------------------------------------
/** \brief  \ru Код подробного сообщения об ошибке при выводе в лог.
            \en The key of a detailed log message.\~   
\ingroup Data_Interface
*/
// ---
enum eMsgDetail { 
  emd_Title,                          ///< \ru Заголовок файла.                 \en File header.
  emd_HEADError,                      ///< \ru Тип сообщения - ошибка.          \en Error.
  emd_HEADWarinig,                    ///< \ru Тип сообщения - Предупреждение.  \en Warning.
  emd_HEADInfo,                       ///< \ru Тип сообщения - Информация.      \en Info.
  emd_HEADDefaultMsg,                 ///< \ru Тип сообщения - Сообщение.       \en Message.

  emd_STOPFileOpenError,              ///< \ru Ошибка открытия файла.                           \en Cannot open file.
  emd_STOPFileOpenErrorOrEmpty,       ///< \ru Ошибка открытия файла или файл пуст.             \en Cannot open file or file is empty.
  emd_STOPHeaderReadError,            ///< \ru Не удалось прочитать заголовок файла.            \en Cannot read file header.
  emd_STOPNoOrBadData,                ///< \ru Файл не содержит данных или их не удалось распознать. \en File body does not exist or incorrect.
  emd_STOPIncorrectStructure,         ///< \ru Неверная структура файла.                        \en Incorrect file structure.
  emd_STOPAddressConflict,            ///< \ru Данный адрес имеют два различных объекта.        \en Two or more entities have the same id.

  emd_ErrorNoRootObject,              ///< \ru Не найден корневой объект.                       \en Root object not found.
  emd_ErrorSyntaxIncorrectFormFloat,  ///< \ru Невозможно прочитать действительную константу.   \en Error reading floating-point number.
  emd_ErrorEmptyLoop,                 ///< \ru Цикл грани пуст.                                 \en Face has an empty loop.
  emd_ErrorEmptyQueriesList,          ///< \ru Список запросов пуст. \en 
  emd_ErrorEmptyObjectsList,          ///< \ru Список объектов пуст.                            \en List of objects is empty.
  emd_ErrorEmptyGeomObjectsList,      ///< \ru Список геометрических объектов пуст.             \en List of geometric objects is empty.
  emd_ErrorEmptyShellsList,           ///< \ru Список оболочек пуст.                            \en List of shells is empty.
  emd_ErrorEmptyListOfWrieframes,     ///< \ru Список каркасов пуст.                            \en List of frames is empty.
  emd_ErrorEmptyCurveCompositesList,  ///< \ru Список компонент составной кривой пуст.          \en Composite curve has an empty list of composites.
  emd_ErrorEmptyBoundCurvesList,      ///< \ru Список граничных кривых пуст.                    \en List of boundary curves is empty.
  emd_ErrorEmptyEdgeList,             ///< \ru Список рёбер пуст.                               \en List of edges is empty.
  emd_ErrorEmptyFacesList,            ///< \ru Список граней пуст.                              \en List of faces is empty.
  emd_ErrorEmptyReferencesList,       ///< \ru Список ссылок пуст.                              \en List of references is empty.
  emd_ErrorEmptyOrMore2ReferencesList,///< \ru Список ссылок пуст или содержит более 2 элементов. \en List of references is empty or contains more than 2 items.
  emd_ErrorUndefinedFaceSurfaceRef,   ///< \ru Ссылка на базовую поверхность грани не определена. \en Invalid reference to base surface.
  emd_ErrorUndefinedBaseCurveRef,     ///< \ru Ссылка на базовую кривую не определена.          \en Invalid reference to base curve.
  emd_ErrorRadiusTooCloseToZero,      ///< \ru Радиус слишком мал.                              \en Too small radius.
  emd_ErrorRadiusValueNegative,       ///< \ru Отрицательное значение радиуса.                  \en Negative value of radius.
  emd_ErrorEllipseAxisTooCloseToZero, ///< \ru Длина полуоси эллипса слишком мала.              \en Ellipse axis is too short.
  emd_ErrorEllipseAxisNegative,       ///< \ru Отрицательная длина полуоси эллипса.             \en Ellipse axis length is negative.
  emd_ErrorNegativeDegree,            ///< \ru Отрицательный порядок сплайна.                   \en Negative spline order.
  emd_ErrorNegativeUDegree,           ///< \ru Отрицательный порядок сплайновой поверхности по U. \en Spline surface order along U is negative.
  emd_ErrorNegativeVDegree,           ///< \ru Отрицательный порядок сплайновой поверхности по V. \en Spline surface order along V is negative.
  emd_ErrorDegreeFixImpossible,       ///< \ru Невозможно исправить порядок сплайна.            \en Cannot fix spline order.
  emd_ErrorPolylinePointListLess2,    ///< \ru Список точек ломаной содержит менее 2 элементов. \en Polyline contains less then 2 points.
  emd_ErrorPointListLess2,            ///< \ru Список точек содержит менее 2 элементов.         \en List of points contains less then 2 points.
  emd_ErrorKnotsListLess2,            ///< \ru Список узлов содержит менее 2 элементов.         \en List of knots contains less then 2 values.
  emd_ErrorWeightsListLess2,          ///< \ru Список весов содержит менее 2 элементов.         \en List of weights contains less then 2 values.
  emd_ErrorUPointListLess2,           ///< \ru Список точек по U содержит менее 2 элементов.    \en List of points along U contains less then 2 points.
  emd_ErrorUKnotsListLess2,           ///< \ru Список узлов по U содержит менее 2 элементов.    \en List of knots along U contains less then 2 values.
  emd_ErrorUWeightsListLess2,         ///< \ru Список весов по U содержит менее 2 элементов.    \en List of weights along U contains less then 2 values.
  emd_ErrorVPointListLess2,           ///< \ru Список точек по V содержит менее 2 элементов.    \en List of points along V contains less then 2 points.
  emd_ErrorVKnotsListLess2,           ///< \ru Список узлов по V содержит менее 2 элементов.    \en List of knots along V contains less then 2 values.
  emd_ErrorVWeightsListLess2,         ///< \ru Список весов по V содержит менее 2 элементов.    \en List of weights along V contains less then 2 values.
  emd_ErrorListsSizeMismatch,         ///< \ru Размеры списков не согласуются.                  \en Lists size mismatch.
  emd_ErrorKnotsWeightsListsOrderMismatch,                ///< \ru Размеры списков узлов и весов не согласуются с порядком сплайна. \en Sizes of knots and weights lists do not agree with the spline order.
  emd_ErrorKnotsWeightsListsSizeMismatch,                 ///< \ru Размеры списков узлов и весов не согласуются. \en Size of knots list does not agree with the size of the list of weights.
  emd_ErrorUKnotsWeightsListsSizeMismatch,                ///< \ru Размеры списков узлов и весов по U не согласуются. \en Sizes of knots and weights lists along U do not agree.
  emd_ErrorVKnotsWeightsListsSizeMismatch,                ///< \ru Размеры списков узлов и весов по V не согласуются. \en Sizes of knots and weights lists along V do not agree.
  emd_ErrorSplineCurveNotCreatedUndefinedKnotsVector,     ///< \ru Сплайновая кривая не создана - не определёны узлы. \en Cannot create spline, because knots are not defined.
  emd_ErrorSplineSurfaceNotCreatedUndefinedKnotsVectors,  ///< \ru Сплайновая поверхность не создана - не определёны узлы. \en Cannot create spline surface, because knots are not defined.
  emd_ErrorInCorrectSplineSurfaceData,                    ///< \ru Неверно заданы параметры NURBS поверхности. \en Spline surface parameters are not valid.

  emd_WarningNoSectionTerminator,             ///< \ru Маркер завершения раздела не обнаружен.  \en Section terminator not found.
  emd_WarningSyntaxMultipleDotInFloat,        ///< \ru Повторяющаяся точка в действительном числе. \en Too many dots in a floating-point number.
  emd_WarningSyntaxMultipleEInFloat,          ///< \ru Повторяющаяся E в действительном числе.  \en Too many E signs in a floating-point number.
  emd_WarningLoopNotClosed,                   ///< \ru Цикл не замкнут.                         \en Loop is not closed.
  emd_WarningContourNotClosed,                ///< \ru Контур не замкнут.                       \en contour is not closed.
  emd_WarningUndefinedRef,                    ///< \ru Ссылка не определена.                    \en Invalid reference.
  emd_WarningToroidalSurfaceDegenerated,      ///< \ru Тороидальная поверхность вырождена.      \en Toroidal surface is degenerate.
  emd_WarningUndefinedBasisCurve,             ///< \ru Не определена базовая кривая.            \en Base curve not defined.
  emd_WarningUndefinedSweptCurve,             ///< \ru Не определена образующая кривая.         \en Generatrix curve is not defined.
  emd_WarningUndefinedExtrusionDirection,     ///< \ru Не определено направление выдавливания.  \en Extrusion direction is not defined.
  emd_WarningUndefinedAxis,                   ///< \ru Не определена ось.                       \en Axis is not defined.
  emd_WarningUndefinedAxisOfRevolution,       ///< \ru Не определена ось вращения.              \en Rotation axis is not defined.
  emd_WarningUndefinedBasisSurface,           ///< \ru Не определена базовая поверхность.       \en Base surface is not defined.
  emd_WarningUndefinedRepresentation,         ///< \ru Не определено представление.             \en Representation is not defined.
  emd_WarningUndefinedTransformationOperator, ///< \ru Не определён оператор преобразования.    \en Transformation is not defined.
  emd_WarningUndefinedObjectTransformBy,      ///< \ru Не определён объект, по которому ведётся преобразование. \en Basic object of transformation is not defined.
  emd_WarningUndefinedObjectToTransform,      ///< \ru Не определён преобразуемый объект.       \en No object to transform is defined.
  emd_WarningUndefinedCurve,                  ///< \ru Не определена кривая.                    \en Curve is not defined.
  emd_WarningUndefinedCompositeSegment,       ///< \ru Не определён сегмент составной кривой.   \en Composite curve segment is not defined.
  emd_WarningUndefinedDirection,              ///< \ru Не определено направление.               \en Direction is not defined.
  emd_WarningUndefinedAxisDirection,          ///< \ru Не определено направление оси.           \en Axis direction is not defined.
  emd_WarningDegeneratedItemWasSkipped,       ///< \ru Проигнорирован (пропущен) вырожденный объект. \en Degenerate object was missed.
  emd_WarningFloatParceFailureDefaultUsed,    ///< \ru Ошибка разпознавания числа с плавающей точкой, подставлено значение по умолчанию. \en Floating point value couldn't be parced; default value was used.
  emd_WarningIncorrectFaceWasNotAddedToShell, ///< \ru Некорректная грань не была добавлена в оболочку. \en Incorrect face was not added to shell.
  emd_WarningBoundsNotConnectedWithSeams,     ///< \ru Границы замкнутой грани не стыкуются со швами. \en Bounds of periodic face not connected with seams.

  emd_MessageWeightsFilled,                        ///< \ru Веса заданы. \en Weights are set.

  emd_ErrorSTEPEdgeCurveFlagTSingleRedefinition,   ///< \ru При создании ребра в конвертере STEP дважды указана грань с флагом .T.. \en Double .T. face inclusion in STEP.
  emd_ErrorSTEPEdgeCurveFlagFSingleRedefinition,   ///< \ru При создании ребра в конвертере STEP дважды указана грань с флагом .F.. \en Double .F. face inclusion in STEP.
  emd_ErrorSTEPEdgeCurveFlagTMultipleRedefinition, ///< \ru При создании ребра в конвертере STEP более чем дважды указана грань с флагом .T.. \en Multiple .T. face inclusion in STEP.
  emd_ErrorSTEPEdgeCurveFlagFMultipleRedefinition, ///< \ru При создании ребра в конвертере STEP более чем дважды указана грань с флагом .F.. \en Multiple .F. face inclusion in STEP.
  emd_ErrorSTEPUndefinedFaceGeometry,   ///< \ru Не определена геометрия грани в конвертере STEP. \en Face geometry is not defined in STEP.
  emd_ErrorSTEPSyntaxMultipleDotInEnum, ///< \ru Синтаксическая ошибка в файле формата STEP - в перечислении символ "." встречается более 1 раза подряд. \en Too many dots in a enumeration record in STEP.
  emd_WarningSTEPPointCorrection,       ///< \ru Скорректированы координаты точки. \en Point location corrected. ( by BUG_73871 )
  emd_WarningSTEPEdgeCurveByVertices,   ///< \ru Кривая ребра скорректирована с учётом координат вершин. \en Edge curve corrected in accordance with vertices. ( by BUG_73871 )
  emd_MessageSTEPFlagChangedToF,        ///< \ru Произведена замена флага на .F.. \en Flag was set as .F. in STEP.
  emd_MessageSTEPFlagChangedToT,        ///< \ru Произведена замена флага на .T.. \en Flag was set as .T. in STEP.

  emd_WarningACISUnsupportedInterpoleCurveType,  ///< \ru Данный подтип ACIS интерполяционной кривой не поддерживается. \en Interpolation curve type is not supported by SAT converter.
  emd_WarningACISUnsupportedParametricCurveType, ///< \ru Данный подтип ACIS параметрической кривой не поддерживается. \en Parametric curve type is not supported by SAT converter.
  emd_ErrorACISUnsupportedVersion,               ///< \ru Данная версия ACIS NT не поддерживается. \en Th version of file is not supported by SAT converter.
  emd_WarningACISCannotImportEntityId,           ///< \ru Не удалось импортировать объект с данным Id. \en Cannot import this object by SAT converter.
  emd_WarningACISIncorrectIntAttribute,          ///< \ru Некорректный целочисленный атрибут. \en Incorrect integer attribute.

  emd_ErrorIGESIncorrectExternalReference,       ///< \ru Неверное имя внешней ссылки. \en Invalid external reference in IGES.

  emd_ErrorSTLTooManyTrianglesForBinary,         ///< \ru Триангуляция исходной модели содержит больше треугольников, чем допустимо стандартом ( не выражается 32-битным беззнаковым числом ) ( by BUG_71422 ). \en Too many triangles (not represented by unsigned 32-bit number) for export to binary STL.

  emd_ErrorXTUnsupportedVersion,                 ///< \ru Данная версия X_T не поддерживается. \en Th version of file is not supported by X_T converter.

  emd_ErrorJTUnsupportedVersion                  ///< \ru Данная версия JT не поддерживается. \en Th version of file is not supported by JT converter.
};


//------------------------------------------------------------------------------
/** \brief \ru Идентификаторы сообщений индикатора прогресса выполнения конвертации данных.
           \en Identifiers of the execution progress indicator messages converters data exchange \~
\ingroup Data_Exchange
*/
//---
enum MbeProgBarId_Converters {
  pbarId_Cnv_Beg = pbarId_PointsSurface_End + 1,

  pbarId_Cnv_Parse_Data,        // \ru Синтаксический анализ... \en Syntactic analysis... 
  pbarId_Cnv_Create_Objects,    // \ru Создание объектов... \en Creation of objects... 
  pbarId_Cnv_Process_Surfaces,  // \ru Обработка поверхностей... \en Surfaces processing... 
  pbarId_Cnv_Process_Annotation,// \ru Обработка аннотации... \en Annotation processing... 
  pbarId_Cnv_Create_Model,      // \ru Создание модели... \en Creation of model... 
  pbarId_Cnv_Write_Model,       // \ru Запись модели... \en Writing of model... 

  pbarId_Cnv_End,
};


//------------------------------------------------------------------------------
/** \brief \ru Идентификаторы сообщений индикатора прогресса выполнения триангуляции при выполнении конвертации данных.
           \en Identifiers of the execution progress indicator messages triangulation. \~
\ingroup Data_Exchange
*/
//---
enum MbeProgBarId_Triangulation {
  pbarId_Triangulation_Beg = pbarId_Cnv_End + 1,

  pbarId_Calc_Triangulation,  // \ru Расчет триангуляции \en Calculating of triangulation 

  pbarId_Triangulation_End,
};


//------------------------------------------------------------------------------
/** \brief \ru Идентификаторы сообщений индикатора прогресса выполнения расчёта 
               масс-инерционные характеристики детали или сборки при выполнении конвертации данных.
           \en Identifiers of the execution progress indicator messages of mass-inertial properties of assembly or a detail. \~
\ingroup Data_Exchange
*/
//---
enum MbeProgBarId_MassInertiaProperties {
  pbarId_MassInertiaProperties_Beg = pbarId_Triangulation_End + 1,

  pbarId_Calc_MassInertiaProperties,  // \ru Расчет масс-инерционных характеристик \en Mass-inertial properties calculation 

  pbarId_MassInertiaProperties_End,
};


#endif // __CONV_ERROR_RESULT_H