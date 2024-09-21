(* Interface-file for a magick-core lib.
 * authors: Monnier Florent (2024)
 * To the extent permitted by law, you can use, modify, and redistribute
 * this file.
 *)

module Low_level = struct

(* genesis / terminus *)

external _magick_core_genesis: string array -> unit = "caml_magick_core_genesis"
external _magick_core_terminus: unit -> unit = "caml_magick_core_terminus"

let magick_core_genesis () =
  _magick_core_genesis Sys.argv;
;;

let () = magick_core_genesis () ;;

let magick_core_terminus = at_exit _magick_core_terminus; _magick_core_terminus ;;

(* exception-info *)

type exception_info

external _magick_exception_info_acquire: unit -> exception_info = "caml_magick_exception_info_acquire"
external _magick_exception_info_destroy: exception_info -> unit = "caml_magick_exception_info_destroy"
external _magick_exception_info_is_null: exception_info -> bool = "caml_magick_exception_info_is_null"

(* image-info *)

type image_info

external _magick_image_info_clone : unit -> image_info = "caml_magick_image_info_clone"
external _magick_image_info_destroy : image_info -> unit = "caml_magick_image_info_destroy"
external _magick_image_info_is_null : image_info -> bool = "caml_magick_image_info_is_null"
external _magick_image_info_clone_some : image_info -> image_info = "caml_magick_image_info_clone_some"

let magick_exception_info_destroy exn_info =
  if _magick_exception_info_is_null exn_info then () else
  _magick_exception_info_destroy exn_info

let magick_image_info_destroy img_info =
  if _magick_image_info_is_null img_info then () else
  _magick_image_info_destroy img_info

let magick_exception_info_acquire () =
  let exn_info = _magick_exception_info_acquire () in
  Gc.finalise magick_exception_info_destroy exn_info;
  (exn_info)
;;

let magick_image_info_clone () =
  let img_info = _magick_image_info_clone () in
  Gc.finalise magick_image_info_destroy img_info;
  (img_info)
;;

let magick_image_info_clone_some img_info =
  let img_info2 = _magick_image_info_clone_some img_info in
  Gc.finalise magick_image_info_destroy img_info2;
  (img_info2)
;;

external magick_image_info_set_filename : image_info -> string -> unit
  = "caml_magick_image_info_set_filename"

external _magick_image_info_set_size : image_info -> string -> unit
  = "caml_magick_image_info_set_size"

let magick_image_info_set_size img_info size =
  _magick_image_info_set_size img_info size;
  ()
;;

(* image *)

type image

external magick_image_destroy : image -> unit
  = "caml_magick_image_destroy"

external magick_image_set_filename : image -> string -> unit
  = "caml_magick_image_set_filename"

(* read / write *)

external magick_image_read : image_info -> exception_info -> image
  = "caml_magick_image_read"

external magick_image_write : image_info -> image -> unit
  = "caml_magick_image_write"

(* display *)

external magick_image_display : image_info -> image -> unit
  = "caml_magick_image_display"

(* effects *)

external magick_image_blur : image -> radius:float -> sigma:float -> exception_info -> image
  = "caml_magick_image_blur"

external magick_image_spread : image -> radius:float -> exception_info -> image
  = "caml_magick_image_spread"

external magick_image_sharpen : image -> radius:float -> sigma:float -> exception_info -> image
  = "caml_magick_image_sharpen"

external magick_image_shade : image -> gray:bool -> azimuth:float -> elevation:float -> exception_info -> image
  = "caml_magick_image_shade"

external magick_image_emboss : image -> radius:float -> sigma:float -> exception_info -> image
  = "caml_magick_image_emboss"

(* visual-effects *)

external magick_image_charcoal : image -> radius:float -> sigma:float -> exception_info -> image
  = "caml_magick_image_charcoal"

(* enhance *)

external magick_image_modulate : image -> modulate:string -> unit
  = "caml_magick_image_modulate"

(* color-space *)

module ColorSpace = struct
  type t = RGB | GRAY | CMYK | HSL | CMY | Luv | LCHab | LCHuv
  (* you can add more if you want, others are available in the C
     header file. *)
end

external magick_image_colorspace_transform: image -> ColorSpace.t -> unit
  = "caml_magick_image_colorspace_transform"

module CompositeOp = struct
  type t = ColorBurn | ColorDodge | Colorize | Darken | DstAtop | DstIn
    | DstOut | DstOver | Difference | Displace | Dissolve | Exclusion
    | HardLight | Hue | In | Lighten | LinearLight | Luminize | MinusDst
    | Modulate | Multiply | Out | Over | Overlay | Plus | Saturate | Screen
    | SoftLight | SrcAtop | Src | SrcIn | SrcOut | SrcOver | ModulusSubtract
    | Threshold | Xor | DivideDst | Distort | Blur | PegtopLight | VividLight
    | PinLight | LinearDodge | LinearBurn | DivideSrc | MinusSrc | Blend
    | Bumpmap | HardMix
end

external magick_image_composite:
  image -> CompositeOp.t -> image -> int -> int -> unit = "caml_magick_image_composite"

(* draw-info *)

type draw_info

external magick_draw_info_acquire: unit -> draw_info = "caml_magick_draw_info_acquire"
external magick_draw_info_destroy: draw_info -> unit = "caml_magick_draw_info_destroy"

type color = int * int * int * int

external magick_draw_info_set_fill: draw_info -> color -> unit = "caml_magick_draw_info_set_fill"
external magick_draw_info_set_stroke: draw_info -> color -> unit = "caml_magick_draw_info_set_stroke"

external magick_draw_info_set_stroke_width: draw_info -> float -> unit = "caml_magick_draw_info_set_stroke_width"
external magick_draw_info_set_primitive: draw_info -> string -> unit = "caml_magick_draw_info_set_primitive"

external magick_image_draw: image -> draw_info -> unit = "caml_magick_image_draw"


end (* Low_level *)


(* Higher_level *)

module Magick = struct

  module Magick = Low_level

  let image_read filename =
    let e = Magick._magick_exception_info_acquire () in
    let nf = Magick._magick_image_info_clone () in
    Magick.magick_image_info_set_filename nf filename;
    let img = Magick.magick_image_read nf e in
    Magick._magick_exception_info_destroy e;
    Magick._magick_image_info_destroy nf;
    Gc.finalise Magick.magick_image_destroy img;
    (img)

  let image_display img =
    let nf = Magick._magick_image_info_clone () in
    Magick.magick_image_display nf img;
    Magick._magick_image_info_destroy nf;
    ()

  let image_write img ~filename =
    let nf = Magick._magick_image_info_clone () in
    Magick.magick_image_set_filename img filename;
    Magick.magick_image_write nf img;
    Magick._magick_image_info_destroy nf;
    ()

  let image_charcoal img ~radius ~sigma =
    let e = Magick._magick_exception_info_acquire () in
    let img2 = Magick.magick_image_charcoal img ~radius ~sigma e in
    Magick._magick_exception_info_destroy e;
    Gc.finalise Magick.magick_image_destroy img2;
    (img2)

  let image_blur img ~radius ~sigma =
    let e = Magick._magick_exception_info_acquire () in
    let img2 = Magick.magick_image_blur img ~radius ~sigma e in
    Magick._magick_exception_info_destroy e;
    Gc.finalise Magick.magick_image_destroy img2;
    (img2)

  let image_spread img ~radius =
    let e = Magick._magick_exception_info_acquire () in
    let img2 = Magick.magick_image_spread img ~radius e in
    Magick._magick_exception_info_destroy e;
    Gc.finalise Magick.magick_image_destroy img2;
    (img2)

  let image_sharpen img ~radius ~sigma =
    let e = Magick._magick_exception_info_acquire () in
    let img2 = Magick.magick_image_sharpen img ~radius ~sigma e in
    Magick._magick_exception_info_destroy e;
    Gc.finalise Magick.magick_image_destroy img2;
    (img2)

  let image_shade img ~gray ~azimuth ~elevation =
    let e = Magick._magick_exception_info_acquire () in
    let img2 = Magick.magick_image_shade img ~gray ~azimuth ~elevation e in
    Magick._magick_exception_info_destroy e;
    Gc.finalise Magick.magick_image_destroy img2;
    (img2)

  let image_emboss img ~radius ~sigma =
    let e = Magick._magick_exception_info_acquire () in
    let img2 = Magick.magick_image_emboss img ~radius ~sigma e in
    Magick._magick_exception_info_destroy e;
    Gc.finalise Magick.magick_image_destroy img2;
    (img2)

  let image_colorspace_transform img color_space =
    Magick.magick_image_colorspace_transform img color_space;
    ()

  let image_modulate img ~modulate:(brightness, saturation, hue) =
    Magick.magick_image_modulate img ~modulate:(
      Printf.sprintf "%d,%d,%d" brightness saturation hue);
    ()

  let image_brightness img brightness =
    Magick.magick_image_modulate img ~modulate:(
      Printf.sprintf "%d,100,100" brightness);
    ()

  let image_saturation img saturation =
    Magick.magick_image_modulate img ~modulate:(
      Printf.sprintf "100,%d,100" saturation);
    ()

  let image_hue img hue =
    Magick.magick_image_modulate img ~modulate:(
      Printf.sprintf "100,100,%d" hue);
    ()

  let image_composite img1 comp_op img2 x y =
    Magick.magick_image_composite img1 comp_op img2 x y

end

include Low_level

