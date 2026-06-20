/* Stub-file for the `magick-core` library,
 * Authors: Monnier Florent (2024, 2026, )
 * To the extent permitted by law, you can use, study, modify, and re-
 * distribute this file, w/ any spdx standardized license,
 */

/* In order to compile w/ a previous (MAGICK_LIB_VERSION == 6)
 * Please take a earlier version of the bindings,
 */

/* This version of the interface is made to compile with a
 * (MAGICK_LIB_VERSION == 7)
 */

/* IM-7 */
#include <MagickCore/MagickCore.h>

#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/fail.h>
#include <caml/custom.h>

#include <stdio.h>
#include <string.h>


/* (ExceptionInfo *) */

static value Val_exninfo(ExceptionInfo *exception)
{
  value v = caml_alloc(1, Abstract_tag);
  *((ExceptionInfo **) Data_abstract_val(v)) = exception;
  return v;
}

#define Exninfo_val(v) \
  *((ExceptionInfo **) Data_abstract_val(v))


/* (ImageInfo *) */

static value Val_imginfo(ImageInfo *image_info)
{
  value v = caml_alloc(1, Abstract_tag);
  *((ImageInfo **) Data_abstract_val(v)) = image_info;
  return v;
}

#define Imginfo_val(v) \
  *((ImageInfo **) Data_abstract_val(v))


/* (Image *) */

static value Val_img(Image *image)
{
  value v = caml_alloc(1, Abstract_tag);
  *((Image **) Data_abstract_val(v)) = image;
  return v;
}

#define Img_val(v) \
  *((Image **) Data_abstract_val(v))


/* (DrawInfo *) */

static value Val_drawinfo(DrawInfo *draw_info)
{
  value v = caml_alloc(1, Abstract_tag);
  *((DrawInfo **) Data_abstract_val(v)) = draw_info;
  return v;
}

#define Drawinfo_val(v) \
  *((DrawInfo **) Data_abstract_val(v))



/* MagickBooleanType */

#define Val_MagickBoolean(b) \
  (b == MagickTrue ? Val_true : Val_false)

#define MagickBoolean_val(b) \
  (b == Val_true ? MagickTrue : MagickFalse)



/* CompositeOperator */

static const CompositeOperator composite_op_table[] = {
  UndefinedCompositeOp,
  NoCompositeOp,
  ModulusAddCompositeOp,
  AtopCompositeOp,
  BlendCompositeOp,
  BumpmapCompositeOp,
  ChangeMaskCompositeOp,
  ClearCompositeOp,
  ColorBurnCompositeOp,
  ColorDodgeCompositeOp,
  ColorizeCompositeOp,
  CopyBlackCompositeOp,
  CopyBlueCompositeOp,
  CopyCompositeOp,
  CopyCyanCompositeOp,
  CopyGreenCompositeOp,
  CopyMagentaCompositeOp,
  CopyRedCompositeOp,
  CopyYellowCompositeOp,
  DarkenCompositeOp,
  DstAtopCompositeOp,
  DstCompositeOp,
  DstInCompositeOp,
  DstOutCompositeOp,
  DstOverCompositeOp,
  DifferenceCompositeOp,
  DisplaceCompositeOp,
  DissolveCompositeOp,
  ExclusionCompositeOp,
  HardLightCompositeOp,
  HueCompositeOp,
  InCompositeOp,
  LightenCompositeOp,
  LinearLightCompositeOp,
  LuminizeCompositeOp,
  MinusDstCompositeOp,
  ModulateCompositeOp,
  MultiplyCompositeOp,
  OutCompositeOp,
  OverCompositeOp,
  OverlayCompositeOp,
  PlusCompositeOp,
  ReplaceCompositeOp,
  SaturateCompositeOp,
  ScreenCompositeOp,
  SoftLightCompositeOp,
  SrcAtopCompositeOp,
  SrcCompositeOp,
  SrcInCompositeOp,
  SrcOutCompositeOp,
  SrcOverCompositeOp,
  ModulusSubtractCompositeOp,
  ThresholdCompositeOp,
  XorCompositeOp,
  DivideDstCompositeOp,
  DistortCompositeOp,
  BlurCompositeOp,
  PegtopLightCompositeOp,
  VividLightCompositeOp,
  PinLightCompositeOp,
  LinearDodgeCompositeOp,
  LinearBurnCompositeOp,
  MathematicsCompositeOp,
  DivideSrcCompositeOp,
  MinusSrcCompositeOp,
  DarkenIntensityCompositeOp,
  LightenIntensityCompositeOp,
  HardMixCompositeOp,
  StereoCompositeOp
};

#define Compositeop_val(v) \
  composite_op_table[Long_val(v)]



/* MagickCoreGenesis() */

CAMLprim value
caml_magick_core_genesis(value caml_argv)
{
  CAMLparam1(caml_argv);

  MagickCoreGenesis(
    String_val(Field(caml_argv, 0)),
    MagickTrue);

  CAMLreturn(Val_unit);
}

/* MagickCoreTerminus() */

CAMLprim value
caml_magick_core_terminus(value unit)
{
  MagickCoreTerminus();
  return Val_unit;
}

/* AcquireExceptionInfo() */

CAMLprim value
caml_magick_exception_info_acquire(value unit)
{
  CAMLparam1(unit);
  CAMLlocal1(caml_exninfo);

  ExceptionInfo *exception_info = AcquireExceptionInfo();

  if (exception_info == (ExceptionInfo *)NULL) {
    caml_failwith("exception_info_acquire: exception_info-is-null");
  }

  caml_exninfo = Val_exninfo(exception_info);

  CAMLreturn(caml_exninfo);
}

/* DestroyExceptionInfo() */

CAMLprim value
caml_magick_exception_info_destroy(value caml_exninfo)
{
  CAMLparam1(caml_exninfo);

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("exception_info_destroy: exception_info-is-null");
  }

  Exninfo_val(caml_exninfo) = DestroyExceptionInfo(exception);

  CAMLreturn(Val_unit);
}

CAMLprim value
caml_magick_exception_info_is_null(value caml_exninfo)
{
  CAMLparam1(caml_exninfo);
  value answer;

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  if (exception == (ExceptionInfo *)NULL) {
    answer = Val_true;
  } else {
    answer = Val_false;
  }

  CAMLreturn(answer);
}

/* (ExceptionInfo *)->reason */

CAMLprim value
caml_magick_exception_info_reason(value caml_exninfo)
{
  CAMLparam1(caml_exninfo);

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("exception_info_reason: exception_info-is-null");
  }

  CAMLreturn(
    (exception->reason) == (char *)NULL ?
    caml_copy_string("") :
    caml_copy_string(exception->reason)
  );
}

/* (ExceptionInfo *)->description */

CAMLprim value
caml_magick_exception_info_description(value caml_exninfo)
{
  CAMLparam1(caml_exninfo);

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("exception_info_description: exception_info-is-null");
  }

  CAMLreturn(
    (exception->description) == (char *)NULL ?
    caml_copy_string("") :
    caml_copy_string(exception->description)
  );
}

/* ExceptionType */

CAMLprim value
caml_magick_exception_info_severity(value caml_exninfo)
{
  CAMLparam1(caml_exninfo);
  value caml_exception_type;

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("exception_info_severity: exception_info-is-null");
  }

  switch (exception->severity)
  {
    case UndefinedException    : caml_exception_type = Val_int(0); break;
    case WarningException      : caml_exception_type = Val_int(1); break;
    case TypeWarning           : caml_exception_type = Val_int(2); break;
    case OptionWarning         : caml_exception_type = Val_int(3); break;
    case DelegateWarning       : caml_exception_type = Val_int(4); break;
    case MissingDelegateWarning: caml_exception_type = Val_int(5); break;
    case CorruptImageWarning   : caml_exception_type = Val_int(6); break;
    case FileOpenWarning       : caml_exception_type = Val_int(7); break;
    case BlobWarning           : caml_exception_type = Val_int(8); break;
    case StreamWarning         : caml_exception_type = Val_int(9); break;
    case CacheWarning          : caml_exception_type = Val_int(10); break;
    case CoderWarning          : caml_exception_type = Val_int(11); break;
    case FilterWarning         : caml_exception_type = Val_int(12); break;
    case ModuleWarning         : caml_exception_type = Val_int(13); break;
    case DrawWarning           : caml_exception_type = Val_int(14); break;
    case ImageWarning          : caml_exception_type = Val_int(15); break;
    case WandWarning           : caml_exception_type = Val_int(16); break;
    case RandomWarning         : caml_exception_type = Val_int(17); break;
    case XServerWarning        : caml_exception_type = Val_int(18); break;
    case MonitorWarning        : caml_exception_type = Val_int(19); break;
    case RegistryWarning       : caml_exception_type = Val_int(20); break;
    case ConfigureWarning      : caml_exception_type = Val_int(21); break;
    case PolicyWarning         : caml_exception_type = Val_int(22); break;
    case ErrorException        : caml_exception_type = Val_int(23); break;
    case TypeError             : caml_exception_type = Val_int(24); break;
    case OptionError           : caml_exception_type = Val_int(25); break;
    case DelegateError         : caml_exception_type = Val_int(26); break;
    case MissingDelegateError  : caml_exception_type = Val_int(27); break;
    case CorruptImageError     : caml_exception_type = Val_int(28); break;
    case FileOpenError         : caml_exception_type = Val_int(29); break;
    case BlobError             : caml_exception_type = Val_int(30); break;
    case StreamError           : caml_exception_type = Val_int(31); break;
    case CacheError            : caml_exception_type = Val_int(32); break;
    case CoderError            : caml_exception_type = Val_int(33); break;
    case FilterError           : caml_exception_type = Val_int(34); break;
    case ModuleError           : caml_exception_type = Val_int(35); break;
    case DrawError             : caml_exception_type = Val_int(36); break;
    case ImageError            : caml_exception_type = Val_int(37); break;
    case WandError             : caml_exception_type = Val_int(38); break;
    case RandomError           : caml_exception_type = Val_int(39); break;
    case XServerError          : caml_exception_type = Val_int(40); break;
    case MonitorError          : caml_exception_type = Val_int(41); break;
    case RegistryError         : caml_exception_type = Val_int(42); break;
    case ConfigureError        : caml_exception_type = Val_int(43); break;
    case PolicyError           : caml_exception_type = Val_int(44); break;
    case FatalErrorException   : caml_exception_type = Val_int(45); break;
    case TypeFatalError           : caml_exception_type = Val_int(46); break;
    case OptionFatalError         : caml_exception_type = Val_int(47); break;
    case DelegateFatalError       : caml_exception_type = Val_int(48); break;
    case MissingDelegateFatalError: caml_exception_type = Val_int(49); break;
    case CorruptImageFatalError   : caml_exception_type = Val_int(50); break;
    case FileOpenFatalError       : caml_exception_type = Val_int(51); break;
    case BlobFatalError           : caml_exception_type = Val_int(52); break;
    case StreamFatalError         : caml_exception_type = Val_int(53); break;
    case CacheFatalError          : caml_exception_type = Val_int(54); break;
    case CoderFatalError          : caml_exception_type = Val_int(55); break;
    case FilterFatalError         : caml_exception_type = Val_int(56); break;
    case ModuleFatalError         : caml_exception_type = Val_int(57); break;
    case DrawFatalError           : caml_exception_type = Val_int(58); break;
    case ImageFatalError          : caml_exception_type = Val_int(59); break;
    case WandFatalError           : caml_exception_type = Val_int(60); break;
    case RandomFatalError         : caml_exception_type = Val_int(61); break;
    case XServerFatalError        : caml_exception_type = Val_int(62); break;
    case MonitorFatalError        : caml_exception_type = Val_int(63); break;
    case RegistryFatalError       : caml_exception_type = Val_int(64); break;
    case ConfigureFatalError      : caml_exception_type = Val_int(65); break;
    case PolicyFatalError         : caml_exception_type = Val_int(66); break;

    default: caml_exception_type = Val_int(67); break;
  }

  CAMLreturn(caml_exception_type);
}

/* CloneImageInfo() */

CAMLprim value
caml_magick_image_info_clone(value unit)
{
  CAMLparam1(unit);
  CAMLlocal1(caml_imginfo);

  ImageInfo *image_info = CloneImageInfo((ImageInfo *)NULL);

  if (image_info == (ImageInfo *)NULL) {
    caml_failwith("image_info_clone: image_info-is-null");
  }

  caml_imginfo = Val_imginfo(image_info);

  CAMLreturn(caml_imginfo);
}

CAMLprim value
caml_magick_image_info_clone_some(value caml_imginfo)
{
  CAMLparam1(caml_imginfo);
  CAMLlocal1(caml_imginfo_2);

  ImageInfo *image_info = Imginfo_val(caml_imginfo);

  if (image_info == (ImageInfo *)NULL) {
    caml_failwith("image_info_clone_some: image_info-is-null");
  }

  ImageInfo *image_info2 = CloneImageInfo(image_info);

  if (image_info2 == (ImageInfo *)NULL) {
    caml_failwith("image_info_clone_some: image_info2-is-null");
  }

  caml_imginfo_2 = Val_imginfo(image_info2);

  CAMLreturn(caml_imginfo_2);
}

CAMLprim value
caml_magick_image_info_is_null(value caml_imginfo)
{
  CAMLparam1(caml_imginfo);
  value answer;

  ImageInfo *image_info = Imginfo_val(caml_imginfo);

  if (image_info == (ImageInfo *)NULL) {
    answer = Val_true;
  } else {
    answer = Val_false;
  }

  CAMLreturn(answer);
}

/* DestroyImageInfo() */

CAMLprim value
caml_magick_image_info_destroy(value caml_imginfo)
{
  CAMLparam1(caml_imginfo);

  ImageInfo *image_info = Imginfo_val(caml_imginfo);

  if (image_info == (ImageInfo *)NULL) {
    caml_failwith("image_info_destroy: image_info-is-null");
  }

  Imginfo_val(caml_imginfo) = DestroyImageInfo(image_info);

  CAMLreturn(Val_unit);
}

/* DestroyImage() */

CAMLprim value
caml_magick_image_destroy(value caml_image)
{
  CAMLparam1(caml_image);

  Image *image = Img_val(caml_image);

  if (image == (Image *)NULL) {
    caml_failwith("image_destroy: image-is-null");
  }

  Img_val(caml_image) = DestroyImage(image);

  CAMLreturn(Val_unit);
}

/* (Image *)->filename[4096] */

CAMLprim value
caml_magick_image_set_filename(
    value caml_image,
    value caml_filename)
{
  CAMLparam2(caml_image, caml_filename);

  Image *image = Img_val(caml_image);
  size_t len;

  if (image == (Image *)NULL) {
    caml_failwith("image_set_filename: image-is-null");
  }

  len = (size_t) caml_string_length(caml_filename);

  if (len >= MaxTextExtent) {
    caml_failwith("image->set_filename: filename too long");
  }

  strncpy(image->filename,
    String_val(caml_filename), len + 1);

  CAMLreturn(Val_unit);
}

/* (ImageInfo *)->filename[4096] */

CAMLprim value
caml_magick_image_info_set_filename(
    value caml_imginfo,
    value caml_filename)
{
  CAMLparam2(caml_imginfo, caml_filename);

  ImageInfo *image_info = Imginfo_val(caml_imginfo);
  size_t len;

  if (image_info == (ImageInfo *)NULL) {
    caml_failwith("image_info_set_filename: image_info-is-null");
  }

  len = (size_t) caml_string_length(caml_filename);

  if (len >= MaxTextExtent) {
    caml_failwith("image_info->set_filename: filename too long");
  }

  strncpy(image_info->filename,
    String_val(caml_filename), len + 1);

  CAMLreturn(Val_unit);
}

/* (ImageInfo *)->size: (char *) */

CAMLprim value
caml_magick_image_info_set_size(
    value caml_imginfo,
    value caml_size)
{
  CAMLparam2(caml_imginfo, caml_size);

  ImageInfo *image_info = Imginfo_val(caml_imginfo);

  if (image_info == (ImageInfo *)NULL) {
    caml_failwith("image_info_set_size: image_info-is-null");
  }

  image_info->size = AcquireString(String_val(caml_size));

  CAMLreturn(Val_unit);
}

/* ReadImage() */

CAMLprim value
caml_magick_image_read(
    value caml_imginfo,
    value caml_exninfo)
{
  CAMLparam2(caml_imginfo, caml_exninfo);
  CAMLlocal1(caml_image);

  ImageInfo *image_info = Imginfo_val(caml_imginfo);
  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  Image *image;

  if (image_info == (ImageInfo *)NULL) {
    caml_failwith("magick_image_read: image_info-is-null");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("magick_image_read: exception_info-is-null");
  }

  image = ReadImage(image_info, exception);

  if (exception->severity != UndefinedException)
  {
    caml_failwith("magick_image_read: error-reading-image");
  }

  if (image == (Image *)NULL) {
    caml_failwith("magick_image_read: image-is-null");
  }

  caml_image = Val_img(image);

  CAMLreturn(caml_image);
}

/* NewMagickImage() */

CAMLprim value
caml_magick_image_create(
    value caml_imginfo,
    value caml_width,
    value caml_height,
    value caml_color,
    value caml_exninfo)
{
  CAMLparam5(caml_imginfo, caml_width, caml_height, caml_color, caml_exninfo);
  CAMLlocal1(caml_image);

  ImageInfo *image_info = Imginfo_val(caml_imginfo);

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  Image *image;

  if (image_info == (ImageInfo *)NULL) {
    caml_failwith("image_create: image_info-is-null");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("image_create: exception_info-is-null");
  }

  /*
  MagickPixelPacket pixel_packet;

  pixel_packet.red     = Long_val(Field(caml_color, 0));
  pixel_packet.green   = Long_val(Field(caml_color, 1));
  pixel_packet.blue    = Long_val(Field(caml_color, 2));
  pixel_packet.opacity = Long_val(Field(caml_color, 3));
  */

  size_t width = Long_val(caml_width);
  size_t height = Long_val(caml_height);

  PixelInfo background;

  background.red   = Long_val(Field(caml_color, 0));
  background.green = Long_val(Field(caml_color, 1));
  background.blue  = Long_val(Field(caml_color, 2));
  background.alpha = Long_val(Field(caml_color, 3));

  //background.storage_class = DirectClass;
  //background.storage_class = PseudoClass;

  background.colorspace = RGBColorspace;

  /*

  ColorspaceType
    colorspace;

  PixelTrait
    alpha_trait;

  double
    fuzz;

  size_t
    depth;

  MagickSizeType
    count;

  */

  image =
    NewMagickImage(image_info,
        width, height, &background, exception);

  /*
  Image *NewMagickImage(
    const ImageInfo *image_info,
    const size_t width,
    const size_t height,
    const PixelInfo *background,
    ExceptionInfo *exception)
  */

  if (image == (Image *)NULL) {
    caml_failwith("image_create: returned-image-is-null");
  }

  caml_image = Val_img(image);

  CAMLreturn(caml_image);
}

/* WriteImage() */

CAMLprim value
caml_magick_image_write(
    value caml_imginfo,
    value caml_image,
    value caml_exninfo)
{
  CAMLparam3(caml_imginfo, caml_image, caml_exninfo);

  ImageInfo *image_info = Imginfo_val(caml_imginfo);

  Image *image = Img_val(caml_image);

  if (image == (Image *)NULL) {
    caml_failwith("image_write: image-is-null");
  }

  ExceptionInfo *exception_info = Exninfo_val(caml_exninfo);

  if (image_info == (ImageInfo *)NULL) {
    caml_failwith("image_write: image_info-is-null");
  }

  if (image == (Image *)NULL) {
    caml_failwith("image_write: image-is-null");
  }

  if (exception_info == (ExceptionInfo *)NULL) {
    caml_failwith("image_write: exception_info-is-null");
  }

  if (!WriteImage(image_info, image, exception_info)) {
    caml_failwith("image_write: error writing image");
  }

  if (exception_info->severity != UndefinedException)
  {
    caml_failwith("image_write: exception while writing image");
  }

  CAMLreturn(Val_unit);
}

/* BlurImage() */

CAMLprim value
caml_magick_image_blur(
    value caml_image, value radius, value sigma,
    value caml_exninfo)
{
  CAMLparam4(caml_image, caml_exninfo, radius, sigma);
  CAMLlocal1(caml_blurred_image);

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  Image *image = Img_val(caml_image);
  Image *blurred_image;

  if (image == (Image *)NULL) {
    caml_failwith("image_blur: image-is-null");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("image_blur: exception_info-is-null");
  }

  blurred_image = BlurImage(image, Double_val(radius), Double_val(sigma), exception);

  if (!blurred_image) {
    caml_failwith("image_blur: error image blur");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("image_blur: exception while bluring image");
  }

  caml_blurred_image = Val_img(blurred_image);

  CAMLreturn(caml_blurred_image);
}

/* CharcoalImage() */

CAMLprim value
caml_magick_image_charcoal(
    value caml_image, value radius, value sigma,
    value caml_exninfo)
{
  CAMLparam4(caml_image, caml_exninfo, radius, sigma);
  CAMLlocal1(caml_image_2);

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  Image *image = Img_val(caml_image);
  Image *image_2;

  if (image == (Image *)NULL) {
    caml_failwith("image_charcoal: image-is-null");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("image_charcoal: exception_info-is-null");
  }

  image_2 = CharcoalImage(image, Double_val(radius), Double_val(sigma), exception);

  if (!image_2) {
    caml_failwith("image_charcoal: error-image-is-null");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("image_charcoal: exception-image-charcoal");
  }

  caml_image_2 = Val_img(image_2);

  CAMLreturn(caml_image_2);
}

/* AddNoiseImage() */

static const NoiseType noise_type_table[] = {
  UndefinedNoise,
  UniformNoise,
  GaussianNoise,
  MultiplicativeGaussianNoise,
  ImpulseNoise,
  LaplacianNoise,
  PoissonNoise,
  RandomNoise
};

CAMLprim value
caml_magick_image_add_noise(
    value caml_image,
    value caml_noise_type,
    value caml_attenuate,
    value caml_exninfo)
{
  CAMLparam4(caml_image, caml_noise_type, caml_attenuate, caml_exninfo);
  CAMLlocal1(caml_image_2);

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  Image *image = Img_val(caml_image);
  Image *image_2;
  NoiseType noise_type;

  if (image == (Image *)NULL) {
    caml_failwith("add_noise: image-is-null");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("add_noise: exception_info-is-null");
  }

  noise_type = noise_type_table[Long_val(caml_noise_type)];
  double attenuate = Double_val(caml_attenuate);

  image_2 = AddNoiseImage(image, noise_type, attenuate, exception);

  if (image_2 == (Image *)NULL) {
    caml_failwith("add_noise: error-image-is-null");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("add_noise: exception-image-add_noise");
  }

  caml_image_2 = Val_img(image_2);

  CAMLreturn(caml_image_2);
}

/* ShadeImage() */

CAMLprim value
caml_magick_image_shade(
    value caml_image, value gray, value azimuth, value elevation,
    value caml_exninfo)
{
  CAMLparam5(caml_image, caml_exninfo, gray, azimuth, elevation);
  CAMLlocal1(caml_image_2);

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  Image *image = Img_val(caml_image);
  Image *image_2;

  if (image == (Image *)NULL) {
    caml_failwith("shade: provided-image-is-null");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("shade: exception_info-is-null");
  }

  image_2 = ShadeImage(image, MagickBoolean_val(gray),
     Double_val(azimuth), Double_val(elevation), exception);

  if (!image_2) {
    caml_failwith("shade: error-returned-image-is-null");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("shade: exception-image-shade");
  }

  caml_image_2 = Val_img(image_2);

  CAMLreturn(caml_image_2);
}

/* SharpenImage() */

CAMLprim value
caml_magick_image_sharpen(
    value caml_image, value radius, value sigma,
    value caml_exninfo)
{
  CAMLparam4(caml_image, caml_exninfo, radius, sigma);
  CAMLlocal1(caml_image_2);

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  Image *image = Img_val(caml_image);
  Image *image_2;

  if (image == (Image *)NULL) {
    caml_failwith("sharpen: image-is-null");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("sharpen: exception_info-is-null");
  }

  image_2 = SharpenImage(image, Double_val(radius), Double_val(sigma), exception);

  if (!image_2) {
    caml_failwith("sharpen: error-image-sharpen");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("sharpen: exception-image-sharpen");
  }

  caml_image_2 = Val_img(image_2);

  CAMLreturn(caml_image_2);
}

/* PixelInterpolateMethod[] */

static const PixelInterpolateMethod pixel_interpolate_method_table[] = {
  UndefinedInterpolatePixel,
  AverageInterpolatePixel,
  Average9InterpolatePixel,
  Average16InterpolatePixel,
  BackgroundInterpolatePixel,
  BilinearInterpolatePixel,
  BlendInterpolatePixel,
  CatromInterpolatePixel,
  IntegerInterpolatePixel,
  MeshInterpolatePixel,
  NearestInterpolatePixel,
  SplineInterpolatePixel
};

/* SpreadImage() */

CAMLprim value
caml_magick_image_spread(
    value caml_image, value caml_method, value radius,
    value caml_exninfo)
{
  CAMLparam4(caml_image, caml_method, radius, caml_exninfo);
  CAMLlocal1(caml_image_2);

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  Image *image = Img_val(caml_image);
  Image *image_2;

  PixelInterpolateMethod method;

  method = pixel_interpolate_method_table[Long_val(caml_method)];

  if (image == (Image *)NULL) {
    caml_failwith("spread: image-is-null");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("spread: exception_info-is-null");
  }

  image_2 = SpreadImage(image, method, Double_val(radius), exception);

  if (!image_2) {
    caml_failwith("spread: error-image-spread");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("spread: exception-image-spread");
  }

  caml_image_2 = Val_img(image_2);

  CAMLreturn(caml_image_2);
}

/* EmbossImage() */

CAMLprim value
caml_magick_image_emboss(
    value caml_image, value radius, value sigma,
    value caml_exninfo)
{
  CAMLparam4(caml_image, caml_exninfo, radius, sigma);
  CAMLlocal1(caml_image_2);

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  Image *image = Img_val(caml_image);
  Image *image_2;

  if (image == (Image *)NULL) {
    caml_failwith("emboss: image-is-null");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("emboss: exception_info-is-null");
  }

  image_2 = EmbossImage(image, Double_val(radius), Double_val(sigma), exception);

  if (!image_2) {
    caml_failwith("emboss: error-image-emboss");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("emboss: exception-image-emboss");
  }

  caml_image_2 = Val_img(image_2);

  CAMLreturn(caml_image_2);
}

/* DespeckleImage() */

CAMLprim value
caml_magick_image_despeckle(
    value caml_image,
    value caml_exninfo)
{
  CAMLparam2(caml_image, caml_exninfo);
  CAMLlocal1(caml_image_2);

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  Image *image = Img_val(caml_image);
  Image *image_2;

  if (image == (Image *)NULL) {
    caml_failwith("despeckle: image-is-null");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("despeckle: exception_info-is-null");
  }

  image_2 = DespeckleImage(image, exception);

  if (image_2 == (Image *)NULL) {
    caml_failwith("despeckle: error-despeckle-image");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("despeckle: exception-despeckle-image");
  }

  caml_image_2 = Val_img(image_2);

  CAMLreturn(caml_image_2);
}

/* ModulateImage() */

CAMLprim value
caml_magick_image_modulate(
    value caml_image, value modulate, value caml_exninfo)
{
  CAMLparam3(caml_image, modulate, caml_exninfo);

  Image *image = Img_val(caml_image);
  MagickBooleanType ret;

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  if (image == (Image *)NULL) {
    caml_failwith("modulate: image-is-null");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("modulate: exception_info-is-null");
  }

  ret = ModulateImage(image, String_val(modulate), exception);

  if (ret == MagickFalse)
  {
    caml_failwith("modulate: error-image-modulate");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("modulate: exception-modulate-image");
  }

  CAMLreturn(Val_unit);
}

/* NegateImage() */

CAMLprim value
caml_magick_image_negate(
    value caml_image, value caml_exninfo)
{
  CAMLparam2(caml_image, caml_exninfo);

  Image *image = Img_val(caml_image);

  MagickBooleanType param = MagickFalse;
  MagickBooleanType ret;

  if (image == (Image *)NULL) {
    caml_failwith("negate: image-is-null");
  }

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("negate: exception_info (is-null)");
  }

  ret = NegateImage(image, param, exception);

  if (ret == MagickFalse)
  {
    caml_failwith("negate: return-error");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("negate: exception-negate-image");
  }

  CAMLreturn(Val_unit);
}

/* EqualizeImage() */

CAMLprim value
caml_magick_image_equalize(
    value caml_image, value caml_exninfo)
{
  CAMLparam2(caml_image, caml_exninfo);

  Image *image = Img_val(caml_image);

  if (image == (Image *)NULL) {
    caml_failwith("equalize: image-is-null");
  }

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("equalize: exception_info (is-null)");
  }

  MagickBooleanType ret;

  ret = EqualizeImage(image, exception);

  if (ret == MagickFalse)
  {
    caml_failwith("equalize: return-error");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("equalize: exception-equalize-image");
  }

  CAMLreturn(Val_unit);
}

/* SolarizeImage() */

CAMLprim value
caml_magick_image_solarize(
    value caml_image, value threshold, value caml_exninfo)
{
  CAMLparam3(caml_image, threshold, caml_exninfo);

  Image *image = Img_val(caml_image);
  MagickBooleanType ret;

  if (image == (Image *)NULL) {
    caml_failwith("solarize: image-is-null");
  }

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("solarize: exception_info (is-null)");
  }

  ret = SolarizeImage(image, Double_val(threshold), exception);

  if (ret == MagickFalse)
  {
    caml_failwith("solarize: return-error");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("solarize: exception-solarize-image");
  }

  CAMLreturn(Val_unit);
}

/* EdgeImage() */

CAMLprim value
caml_magick_image_edge(
    value caml_image, value radius, value caml_exninfo)
{
  CAMLparam3(caml_image, radius, caml_exninfo);
  CAMLlocal1(caml_image_2);

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);
  Image *image = Img_val(caml_image);
  Image *image_2;

  if (image == (Image *)NULL) {
    caml_failwith("edge: image-is-null");
  }

  image_2 = EdgeImage(image, Double_val(radius), exception);

  if (image_2 == (Image *)NULL)
  {
    caml_failwith("edge: error-image-is-null");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("edge: exception-edge-image");
  }

  caml_image_2 = Val_img(image_2);

  CAMLreturn(caml_image_2);
}

/* ScaleImage() */

CAMLprim value
caml_magick_image_scale(
    value caml_image, value size, value caml_exninfo)
{
  CAMLparam3(caml_image, size, caml_exninfo);
  CAMLlocal1(caml_image_2);

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);
  Image *image = Img_val(caml_image);
  Image *image_2;

  size_t columns = Long_val(Field(size, 0));
  size_t rows    = Long_val(Field(size, 1));

  if (image == (Image *)NULL) {
    caml_failwith("scale: image-is-null");
  }

  image_2 = ScaleImage(image, columns, rows, exception);

  if (image_2 == (Image *)NULL)
  {
    caml_failwith("scale: error-scale-image");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("scale: exception-scale-image");
  }

  caml_image_2 = Val_img(image_2);

  CAMLreturn(caml_image_2);
}

/* DisplayImages() */

CAMLprim value
caml_magick_image_display(
    value caml_imginfo,
    value caml_image,
    value caml_exninfo)
{
  CAMLparam3(caml_imginfo, caml_image, caml_exninfo);

  ImageInfo *image_info = Imginfo_val(caml_imginfo);
  Image *images = Img_val(caml_image);

  if (image_info == (ImageInfo *)NULL) {
    caml_failwith("display: image_info-is-null");
  }

  if (images == (Image *)NULL) {
    caml_failwith("display: images-eq-null");
  }

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("display: exception_info-is-null");
  }

  MagickBooleanType ret = DisplayImages(image_info, images, exception);

  if (exception->severity != UndefinedException)
  {
    caml_failwith("display: exception-display-image");
  }

  CAMLreturn((ret == MagickTrue ? Val_true : Val_false));
}

/* TransformImageColorspace() */

static const ColorspaceType colorspace_table[] = {
  UndefinedColorspace,
  RGBColorspace,
  GRAYColorspace,
  TransparentColorspace,
  OHTAColorspace,
  LabColorspace,
  XYZColorspace,
  YCbCrColorspace,
  YCCColorspace,
  YIQColorspace,
  YPbPrColorspace,
  YUVColorspace,
  CMYKColorspace,
  sRGBColorspace,
  HSBColorspace,
  HSLColorspace,
  HWBColorspace,
  Rec601YCbCrColorspace,
  Rec709YCbCrColorspace,
  LogColorspace,
  CMYColorspace,
  LuvColorspace,
  HCLColorspace,
  LCHColorspace,
  LMSColorspace,
  LCHabColorspace,
  LCHuvColorspace,
  scRGBColorspace,
  HSIColorspace,
  HSVColorspace,
  HCLpColorspace,
  YDbDrColorspace,
  xyYColorspace,
  LinearGRAYColorspace
};

CAMLprim value
caml_magick_image_colorspace_transform(value caml_image, value caml_colorspace, value caml_exninfo)
{
  CAMLparam3(caml_image, caml_colorspace, caml_exninfo);

  ColorspaceType colorspace_type = colorspace_table[Long_val(caml_colorspace)];

  Image *image = Img_val(caml_image);

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  if (image == (Image *)NULL) {
    caml_failwith("colorspace_transform: image-is-null");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("colorspace_transform: exception_info-is-null");
  }

  /* convert image colorspace */

  if (!TransformImageColorspace(image, colorspace_type, exception)) {
    caml_failwith("colorspace_transform: error converting image colorspace");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("colorspace_transform: exception-returned");
  }

  CAMLreturn(Val_unit);
}

/* CompositeImage() */

CAMLprim value
caml_magick_image_composite(
    value caml_image1,
    value caml_image2,
    value caml_composite_op,
    value caml_xy_offset,
    value caml_exninfo)
{
  CAMLparam5(caml_image1, caml_composite_op, caml_image2, caml_xy_offset, caml_exninfo);

  CompositeOperator composite_op = Compositeop_val(caml_composite_op);

  Image *image1 = Img_val(caml_image1);
  Image *image2 = Img_val(caml_image2);

  if (image1 == (Image *)NULL) {
    caml_failwith("composite: image-1 (is-null)");
  }

  if (image2 == (Image *)NULL) {
    caml_failwith("composite: image-2 (is-null)");
  }

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("composite: exception_info (is-null)");
  }

  value caml_x_offset = Field(caml_xy_offset, 0);
  value caml_y_offset = Field(caml_xy_offset, 1);

  ssize_t x_offset = Long_val(caml_x_offset);
  ssize_t y_offset = Long_val(caml_y_offset);

  MagickBooleanType clip_to_self = MagickTrue;

  MagickBooleanType status =
    CompositeImage(image1, image2, composite_op,
      clip_to_self, x_offset, y_offset, exception);

  if (status == MagickFalse) {
    caml_failwith("composite: error-compositing-images");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("composite: exception-composite-image");
  }

  CAMLreturn(Val_unit);
}

/* AcquireDrawInfo() */

CAMLprim value
caml_magick_draw_info_acquire(
    value caml_unit)
{
  CAMLparam1(caml_unit);
  CAMLlocal1(caml_draw_info);

  DrawInfo *draw_info = AcquireDrawInfo();

  if (draw_info == (DrawInfo *)NULL) {
    caml_failwith("draw_info_acquire: draw_info-is-null");
  }

  caml_draw_info = Val_drawinfo(draw_info);

  CAMLreturn(caml_draw_info);
}

CAMLprim value
caml_magick_draw_info_destroy(
    value caml_draw_info)
{
  CAMLparam1(caml_draw_info);

  DrawInfo *draw_info = Drawinfo_val(caml_draw_info);

  if (draw_info == (DrawInfo *)NULL) {
    caml_failwith("draw_info_destroy: draw_info-is-null");
  }

  DrawInfo *destroyed = DestroyDrawInfo(draw_info);

  if (destroyed != (DrawInfo *)NULL) {
    caml_failwith("draw_info_destroy: not-nullified-properly");
  }

  Drawinfo_val(caml_draw_info) = destroyed;

  CAMLreturn(Val_unit);
}

CAMLprim value
caml_magick_draw_info_set_fill(
    value caml_draw_info,
    value caml_color)
{
  CAMLparam2(caml_draw_info, caml_color);

  DrawInfo *draw_info = Drawinfo_val(caml_draw_info);

  if (draw_info == (DrawInfo *)NULL) {
    caml_failwith("draw_info_set_fill: draw_info-is-null");
  }

  draw_info->fill.red    = Long_val(Field(caml_color, 0));
  draw_info->fill.green  = Long_val(Field(caml_color, 1));
  draw_info->fill.blue   = Long_val(Field(caml_color, 2));
  draw_info->fill.alpha  = Long_val(Field(caml_color, 3));

  CAMLreturn(Val_unit);
}

CAMLprim value
caml_magick_draw_info_set_stroke(
    value caml_draw_info,
    value caml_color)
{
  CAMLparam2(caml_draw_info, caml_color);

  DrawInfo *draw_info = Drawinfo_val(caml_draw_info);

  if (draw_info == (DrawInfo *)NULL) {
    caml_failwith("draw_info_set_stroke: draw_info-is-null");
  }

  draw_info->stroke.red    = Long_val(Field(caml_color, 0));
  draw_info->stroke.green  = Long_val(Field(caml_color, 1));
  draw_info->stroke.blue   = Long_val(Field(caml_color, 2));
  draw_info->stroke.alpha  = Long_val(Field(caml_color, 3));

  CAMLreturn(Val_unit);
}

CAMLprim value
caml_magick_draw_info_set_stroke_width(
    value caml_draw_info,
    value caml_stroke_width)
{
  CAMLparam2(caml_draw_info, caml_stroke_width);

  DrawInfo *draw_info = Drawinfo_val(caml_draw_info);

  if (draw_info == (DrawInfo *)NULL) {
    caml_failwith("draw_info_set_stroke_width: draw_info-is-null");
  }

  draw_info->stroke_width = Double_val(caml_stroke_width);

  CAMLreturn(Val_unit);
}

CAMLprim value
caml_magick_draw_info_set_compose(
    value caml_draw_info,
    value caml_compose)
{
  CAMLparam2(caml_draw_info, caml_compose);

  DrawInfo *draw_info = Drawinfo_val(caml_draw_info);

  if (draw_info == (DrawInfo *)NULL) {
    caml_failwith("draw_info_set_compose: draw_info-is-null");
  }

  draw_info->compose = Compositeop_val(caml_compose);

  CAMLreturn(Val_unit);
}

CAMLprim value
caml_magick_draw_info_set_primitive(
    value caml_draw_info,
    value caml_primitive)
{
  CAMLparam2(caml_draw_info, caml_primitive);

  DrawInfo *draw_info = Drawinfo_val(caml_draw_info);

  if (draw_info == (DrawInfo *)NULL) {
    caml_failwith("draw_info_set_primitive: draw_info-is-null");
  }

  if (draw_info->primitive != (char *)NULL) {
    draw_info->primitive = DestroyString(draw_info->primitive);
  }

  draw_info->primitive = AcquireString(String_val(caml_primitive));

  CAMLreturn(Val_unit);
}

CAMLprim value
caml_magick_draw_info_set_font(
    value caml_draw_info,
    value caml_font)
{
  CAMLparam2(caml_draw_info, caml_font);

  DrawInfo *draw_info = Drawinfo_val(caml_draw_info);

  if (draw_info == (DrawInfo *)NULL) {
    caml_failwith("draw_info_set_font: draw_info-is-null");
  }

  if (draw_info->font != (char *)NULL) {
    draw_info->font = DestroyString(draw_info->font);
  }

  draw_info->font = AcquireString(String_val(caml_font));

  CAMLreturn(Val_unit);
}

CAMLprim value
caml_magick_draw_info_set_pointsize(
    value caml_draw_info,
    value caml_pointsize)
{
  CAMLparam2(caml_draw_info, caml_pointsize);

  DrawInfo *draw_info = Drawinfo_val(caml_draw_info);

  if (draw_info == (DrawInfo *)NULL) {
    caml_failwith("draw_info_set_pointsize: draw_info-is-null");
  }

  draw_info->pointsize = Double_val(caml_pointsize);

  CAMLreturn(Val_unit);
}

CAMLprim value
caml_magick_image_draw(
    value caml_image,
    value caml_draw_info,
    value caml_exninfo)
{
  CAMLparam3(caml_image, caml_draw_info, caml_exninfo);

  DrawInfo *draw_info = Drawinfo_val(caml_draw_info);

  Image *image = Img_val(caml_image);

  if (draw_info == (DrawInfo *)NULL) {
    caml_failwith("magick_image_draw: draw_info-is-null");
  }

  if (image == (Image *)NULL) {
    caml_failwith("magick_image_draw: image-is-null");
  }

  ExceptionInfo *exception_info = Exninfo_val(caml_exninfo);

  if (exception_info == (ExceptionInfo *)NULL) {
    caml_failwith("magick_image_draw: exception_info-is-null");
  }

  MagickBooleanType status = DrawImage(image, draw_info, exception_info);

  if (status == MagickFalse) {
    caml_failwith("magick_image_draw: error-drawing-image");
  }

  if (exception_info->severity != UndefinedException)
  {
    caml_failwith("magick_image_draw: exception-draw-image");
  }

  CAMLreturn(Val_unit);
}

/* (QuantumRange) */

CAMLprim value
caml_magick_get_quantum_range(
    value caml_unit)
{
  CAMLparam1(caml_unit);
  CAMLlocal1(caml_quantum_range);

  caml_quantum_range = caml_copy_double(QuantumRange);

  CAMLreturn(caml_quantum_range);
}

/* (QuantumScale) */

CAMLprim value
caml_magick_get_quantum_scale(
    value caml_unit)
{
  CAMLparam1(caml_unit);
  CAMLlocal1(caml_quantum_scale);

  caml_quantum_scale = caml_copy_double(QuantumScale);

  CAMLreturn(caml_quantum_scale);
}

/* (MaxMap) */

CAMLprim value
caml_magick_get_max_map(value unit) {
  return Val_long(MaxMap);
}

/* (MaxColormapSize) */

CAMLprim value
caml_magick_get_max_colormap_size(value unit) {
  return Val_long(MaxColormapSize);
}

/* (MAGICKCORE_QUANTUM_DEPTH) */

CAMLprim value
caml_magick_get_quantum_depth(value unit) {
  return Val_long(MAGICKCORE_QUANTUM_DEPTH);
}

