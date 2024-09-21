(** A Magick-Interface *)
(* Interface-file for a magick-core lib.
 * Authors: Monnier Florent (2024)
 * To the extent permitted by law, you can use, modify, and redistribute
 * this file.
 *)

(* genesis / terminus *)

val magick_core_genesis : unit -> unit
val magick_core_terminus : unit -> unit

(* exception-info *)

type exception_info

val magick_exception_info_acquire : unit -> exception_info
val magick_exception_info_destroy : exception_info -> unit

(* image-info *)

type image_info

val magick_image_info_clone : unit -> image_info
val magick_image_info_destroy : image_info -> unit

val magick_image_info_clone_some : image_info -> image_info

val magick_image_info_set_filename : image_info -> string -> unit
val magick_image_info_set_size : image_info -> string -> unit

external _magick_exception_info_acquire: unit -> exception_info = "caml_magick_exception_info_acquire"
external _magick_exception_info_destroy: exception_info -> unit = "caml_magick_exception_info_destroy"

external _magick_image_info_clone : unit -> image_info = "caml_magick_image_info_clone"
external _magick_image_info_destroy : image_info -> unit = "caml_magick_image_info_destroy"
external _magick_image_info_clone_some : image_info -> image_info = "caml_magick_image_info_clone_some"

external _magick_image_info_set_size : image_info -> string -> unit
  = "caml_magick_image_info_set_size"

external _magick_image_info_is_null : image_info -> bool
  = "caml_magick_image_info_is_null"

external _magick_core_genesis: string array -> unit = "caml_magick_core_genesis"
external _magick_core_terminus: unit -> unit = "caml_magick_core_terminus"

(* image *)

type image

val magick_image_destroy : image -> unit
val magick_image_set_filename : image -> string -> unit

(* read / write *)

val magick_image_read : image_info -> exception_info -> image
val magick_image_write : image_info -> image -> unit

(* display *)

val magick_image_display : image_info -> image -> unit

(* effects *)

val magick_image_blur :
  image -> radius:float -> sigma:float -> exception_info -> image

val magick_image_spread :
  image -> radius:float -> exception_info -> image

val magick_image_sharpen :
  image -> radius:float -> sigma:float -> exception_info -> image

val magick_image_shade :
  image -> gray:bool -> azimuth:float -> elevation:float -> exception_info -> image

val magick_image_emboss :
  image -> radius:float -> sigma:float -> exception_info -> image

(* visual-effects *)

val magick_image_charcoal :
  image -> radius:float -> sigma:float -> exception_info -> image

(* enhance *)

val magick_image_modulate : image -> modulate:string -> unit
(* modulate:(brightness, saturation, hue), default is 100 *)

(* color-space *)

module ColorSpace : sig
  type t = RGB | GRAY | CMYK | HSL | CMY | Luv | LCHab | LCHuv
end

val magick_image_colorspace_transform : image -> ColorSpace.t -> unit

module CompositeOp : sig
  type t = ColorBurn | ColorDodge | Colorize | Darken | DstAtop | DstIn
    | DstOut | DstOver | Difference | Displace | Dissolve | Exclusion
    | HardLight | Hue | In | Lighten | LinearLight | Luminize | MinusDst
    | Modulate | Multiply | Out | Over | Overlay | Plus | Saturate | Screen
    | SoftLight | SrcAtop | Src | SrcIn | SrcOut | SrcOver | ModulusSubtract
    | Threshold | Xor | DivideDst | Distort | Blur | PegtopLight | VividLight
    | PinLight | LinearDodge | LinearBurn | DivideSrc | MinusSrc | Blend
    | Bumpmap | HardMix
end

val magick_image_composite : image -> CompositeOp.t -> image -> int -> int -> unit

(* draw-info *)

type draw_info

val magick_draw_info_acquire: unit -> draw_info
val magick_draw_info_destroy: draw_info -> unit

type color = int * int * int * int

val magick_draw_info_set_fill: draw_info -> color -> unit
val magick_draw_info_set_stroke: draw_info -> color -> unit

val magick_draw_info_set_stroke_width: draw_info -> float -> unit
val magick_draw_info_set_primitive: draw_info -> string -> unit

val magick_image_draw: image -> draw_info -> unit


(* high-level *)

module Magick : sig
  (** higher-level module *)
  val image_read : string -> image
  val image_display : image -> unit
  val image_write : image -> filename:string -> unit
  val image_charcoal : image -> radius:float -> sigma:float -> image
  val image_blur : image -> radius:float -> sigma:float -> image
  val image_spread : image -> radius:float -> image
  val image_sharpen : image -> radius:float -> sigma:float -> image
  val image_shade : image -> gray:bool -> azimuth:float -> elevation:float -> image
  val image_emboss : image -> radius:float -> sigma:float -> image
  val image_colorspace_transform : image -> ColorSpace.t -> unit
  val image_composite : image -> CompositeOp.t -> image -> int -> int -> unit
  val image_modulate : image -> modulate:(int * int * int) -> unit
  (* modulates: *)
  val image_brightness : image -> int -> unit
  val image_saturation : image -> int -> unit
  val image_hue : image -> int -> unit
end

