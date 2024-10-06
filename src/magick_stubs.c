/* Stub-file for the magick-core library
 * Authors: Monnier Florent (2024)
 * To the extent permitted by law, you can use, modify, and redistribute
 * this file.
 */

#ifndef MAGICK_LIB_VERSION
#define MAGICK_LIB_VERSION 6
#endif


#if MAGICK_LIB_VERSION == 6

/* IM-6 */
#include <magick/MagickCore.h>

#endif

#if MAGICK_LIB_VERSION == 7

/* IM-7 */
#include <MagickCore/MagickCore.h>

#endif


#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/fail.h>
#include <caml/custom.h>

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
  value v = caml_alloc(2, Abstract_tag);
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

  ExceptionInfo *exception = AcquireExceptionInfo();
  caml_exninfo = Val_exninfo(exception);

  CAMLreturn(caml_exninfo);
}

/* DestroyExceptionInfo() */

CAMLprim value
caml_magick_exception_info_destroy(value caml_exninfo)
{
  CAMLparam1(caml_exninfo);

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("ExceptionInfo is NULL");
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

/* CloneImageInfo() */

CAMLprim value
caml_magick_image_info_clone(value unit)
{
  CAMLparam1(unit);
  CAMLlocal1(caml_imginfo);

  ImageInfo *image_info = CloneImageInfo((ImageInfo *)NULL);
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
    caml_failwith("ImageInfo is NULL");
  }

  ImageInfo *image_info2 = CloneImageInfo(image_info);
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
    caml_failwith("ImageInfo is NULL");
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
    caml_failwith("Image is NULL");
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
    caml_failwith("Image is NULL");
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
    caml_failwith("ImageInfo is NULL");
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
    caml_failwith("ImageInfo is NULL");
  }

  image_info->size = AcquireString(String_val(caml_size));

  Store_field(caml_imginfo, 1, caml_size);

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
    caml_failwith("ImageInfo is NULL");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("ExceptionInfo is NULL");
  }

  image = ReadImage(image_info, exception);

  if (exception->severity != UndefinedException)
  {
    caml_failwith("Error reading image");
  }

  if (image == (Image *)NULL) {
    caml_failwith("Image is NULL");
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
    value caml_color)
{
  CAMLparam4(caml_imginfo, caml_width, caml_height, caml_color);
  CAMLlocal1(caml_image);

  ImageInfo *image_info = Imginfo_val(caml_imginfo);

  Image *image;

  if (image_info == (ImageInfo *)NULL) {
    caml_failwith("ImageInfo is NULL");
  }

  MagickPixelPacket pixel_packet;

  pixel_packet.red     = Long_val(Field(caml_color, 0));
  pixel_packet.green   = Long_val(Field(caml_color, 1));
  pixel_packet.blue    = Long_val(Field(caml_color, 2));
  pixel_packet.opacity = Long_val(Field(caml_color, 3));

  image =
    NewMagickImage(image_info,
        Long_val(caml_width),
        Long_val(caml_height), &pixel_packet);

  if (image == (Image *)NULL) {
    caml_failwith("Image is NULL");
  }

  caml_image = Val_img(image);

  CAMLreturn(caml_image);
}

/* WriteImage() */

CAMLprim value
caml_magick_image_write(
    value caml_imginfo,
    value caml_image)
{
  CAMLparam2(caml_imginfo, caml_image);

  ImageInfo *image_info = Imginfo_val(caml_imginfo);

  Image *image = Img_val(caml_image);

  if (image_info == (ImageInfo *)NULL) {
    caml_failwith("ImageInfo is NULL");
  }

  if (image == (Image *)NULL) {
    caml_failwith("Image is NULL");
  }

  if (!WriteImage(image_info, image)) {
    caml_failwith("Error writing image");
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
    caml_failwith("Image is NULL");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("ExceptionInfo is NULL");
  }

  blurred_image = BlurImage(image, Double_val(radius), Double_val(sigma), exception);

  if (!blurred_image) {
    caml_failwith("Error image blur");
  }

  caml_blurred_image = Val_img(blurred_image);

  if (exception->severity != UndefinedException)
  {
    caml_failwith("Error while bluring image");
  }

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
    caml_failwith("Image is NULL");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("ExceptionInfo is NULL");
  }

  image_2 = CharcoalImage(image, Double_val(radius), Double_val(sigma), exception);

  if (!image_2) {
    caml_failwith("Error image charcoal");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("Error image charcoal");
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
    caml_failwith("Image is NULL");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("ExceptionInfo is NULL");
  }

  image_2 = ShadeImage(image, MagickBoolean_val(gray),
     Double_val(azimuth), Double_val(elevation), exception);

  if (!image_2) {
    caml_failwith("Error image shade");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("Error image shade");
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
    caml_failwith("Image is NULL");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("ExceptionInfo is NULL");
  }

  image_2 = SharpenImage(image, Double_val(radius), Double_val(sigma), exception);

  if (!image_2) {
    caml_failwith("Error image sharpen");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("Error image sharpen");
  }

  caml_image_2 = Val_img(image_2);

  CAMLreturn(caml_image_2);
}

/* SpreadImage() */

CAMLprim value
caml_magick_image_spread(
    value caml_image, value radius,
    value caml_exninfo)
{
  CAMLparam3(caml_image, caml_exninfo, radius);
  CAMLlocal1(caml_image_2);

  ExceptionInfo *exception = Exninfo_val(caml_exninfo);

  Image *image = Img_val(caml_image);
  Image *image_2;

  if (image == (Image *)NULL) {
    caml_failwith("Image is NULL");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("ExceptionInfo is NULL");
  }

  image_2 = SpreadImage(image, Double_val(radius), exception);

  if (!image_2) {
    caml_failwith("Error image spread");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("Error image spread");
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
    caml_failwith("Image is NULL");
  }

  if (exception == (ExceptionInfo *)NULL) {
    caml_failwith("ExceptionInfo is NULL");
  }

  image_2 = EmbossImage(image, Double_val(radius), Double_val(sigma), exception);

  if (!image_2) {
    caml_failwith("Error image emboss");
  }

  if (exception->severity != UndefinedException)
  {
    caml_failwith("Error image emboss");
  }

  caml_image_2 = Val_img(image_2);

  CAMLreturn(caml_image_2);
}

/* ModulateImage() */

CAMLprim value
caml_magick_image_modulate(
    value caml_image, value modulate)
{
  CAMLparam2(caml_image, modulate);

  Image *image = Img_val(caml_image);
  MagickBooleanType ret;

  if (image == (Image *)NULL) {
    caml_failwith("Image is NULL");
  }

  ret = ModulateImage(image, String_val(modulate));

  if (ret == MagickFalse)
  {
    caml_failwith("Error image modulate");
  }

  CAMLreturn(Val_unit);
}

/* DisplayImages() */

CAMLprim value
caml_magick_image_display(
    value caml_imginfo,
    value caml_image)
{
  CAMLparam2(caml_imginfo, caml_image);

  ImageInfo *image_info = Imginfo_val(caml_imginfo);
  Image *image = Img_val(caml_image);

  if (image_info == (ImageInfo *)NULL) {
    caml_failwith("ImageInfo is NULL");
  }

  if (image == (Image *)NULL) {
    caml_failwith("Image is NULL");
  }

  MagickBooleanType ret = DisplayImages(image_info, image);

  CAMLreturn((ret == MagickTrue ? Val_true : Val_false));
}

/* TransformImageColorspace() */

static const ColorspaceType colorspace_table[] = {
  RGBColorspace,
  GRAYColorspace,
  CMYKColorspace,
  HSLColorspace,
  CMYColorspace,
  LuvColorspace,
  LCHabColorspace,
  LCHuvColorspace,
  /* add more elements here, if you need, from: "magick/colorspace.h" */
};

CAMLprim value
caml_magick_image_colorspace_transform(value caml_image, value caml_colorspace)
{
  CAMLparam2(caml_image, caml_colorspace);

  ColorspaceType colorspace_type = colorspace_table[Long_val(caml_colorspace)];

  Image *image = Img_val(caml_image);

  if (image == (Image *)NULL) {
    caml_failwith("Image is NULL");
  }

  /* convert image colorspace */
  if (!TransformImageColorspace(image, colorspace_type)) {
    caml_failwith("Error converting image colorspace");
  }

  CAMLreturn(Val_unit);
}

/* CompositeImage() */

static const CompositeOperator composite_op_table[] = {
  ColorBurnCompositeOp,
  ColorDodgeCompositeOp,
  ColorizeCompositeOp,
  DarkenCompositeOp,
  DstAtopCompositeOp,
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
  DivideSrcCompositeOp,
  MinusSrcCompositeOp,
  BlendCompositeOp,
  BumpmapCompositeOp,
  HardMixCompositeOp,
  DarkenIntensityCompositeOp,
  LightenIntensityCompositeOp,

  /* add more elements here, if you need, from: "magick/composite.h" */
};

CAMLprim value
caml_magick_image_composite(
    value caml_image1,
    value caml_composite_op,
    value caml_image2, value x, value y)
{
  CAMLparam5(caml_image1, caml_composite_op, caml_image2, x, y);

  CompositeOperator composite_op = composite_op_table[Long_val(caml_composite_op)];

  Image *image1 = Img_val(caml_image1);
  Image *image2 = Img_val(caml_image2);

  if (image1 == (Image *)NULL) {
    caml_failwith("Image is NULL");
  }

  if (image2 == (Image *)NULL) {
    caml_failwith("Image is NULL");
  }

  MagickBooleanType status =
    CompositeImage(image1, composite_op, image2, Long_val(x), Long_val(y));

  if (status == MagickFalse) {
    caml_failwith("Error Compositing images");
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
    caml_failwith("DrawInfo is NULL");
  }

  DrawInfo *destroyed = DestroyDrawInfo(draw_info);

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
    caml_failwith("DrawInfo is NULL");
  }

  draw_info->fill.red     = Long_val(Field(caml_color, 0));
  draw_info->fill.green   = Long_val(Field(caml_color, 1));
  draw_info->fill.blue    = Long_val(Field(caml_color, 2));
  draw_info->fill.opacity = Long_val(Field(caml_color, 3));

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
    caml_failwith("DrawInfo is NULL");
  }

  draw_info->stroke.red     = Long_val(Field(caml_color, 0));
  draw_info->stroke.green   = Long_val(Field(caml_color, 1));
  draw_info->stroke.blue    = Long_val(Field(caml_color, 2));
  draw_info->stroke.opacity = Long_val(Field(caml_color, 3));

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
    caml_failwith("DrawInfo is NULL");
  }

  draw_info->stroke_width = Double_val(caml_stroke_width);

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
    caml_failwith("DrawInfo is NULL");
  }

  draw_info->primitive = AcquireString(String_val(caml_primitive));

  CAMLreturn(Val_unit);
}

CAMLprim value
caml_magick_image_draw(
    value caml_image,
    value caml_draw_info)
{
  CAMLparam2(caml_image, caml_draw_info);

  DrawInfo *draw_info = Drawinfo_val(caml_draw_info);

  Image *image = Img_val(caml_image);

  if (draw_info == (DrawInfo *)NULL) {
    caml_failwith("DrawInfo is NULL");
  }

  if (image == (Image *)NULL) {
    caml_failwith("Image is NULL");
  }

  MagickBooleanType status = DrawImage(image, draw_info);

  if (status == MagickFalse) {
    caml_failwith("Error Drawing image");
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

