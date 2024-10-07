(* Interface-file for a magick-core lib.
 * Authors: Monnier Florent (2024)
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

(* create *)

type color = int * int * int * int

external magick_image_new : image_info -> int -> int -> color -> image
  = "caml_magick_image_create"

(* display *)

external magick_image_display : image_info -> image -> unit
  = "caml_magick_image_display"

(* exception-info *)

type exception_type =
  | UndefinedException
  | WarningException
  | TypeWarning
  | OptionWarning
  | DelegateWarning
  | MissingDelegateWarning
  | CorruptImageWarning
  | FileOpenWarning
  | BlobWarning
  | StreamWarning
  | CacheWarning
  | CoderWarning
  | FilterWarning
  | ModuleWarning
  | DrawWarning
  | ImageWarning
  | WandWarning
  | RandomWarning
  | XServerWarning
  | MonitorWarning
  | RegistryWarning
  | ConfigureWarning
  | PolicyWarning
  | ErrorException
  | TypeError
  | OptionError
  | DelegateError
  | MissingDelegateError
  | CorruptImageError
  | FileOpenError
  | BlobError
  | StreamError
  | CacheError
  | CoderError
  | FilterError
  | ModuleError
  | DrawError
  | ImageError
  | WandError
  | RandomError
  | XServerError
  | MonitorError
  | RegistryError
  | ConfigureError
  | PolicyError
  | FatalErrorException
  | TypeFatalError
  | OptionFatalError
  | DelegateFatalError
  | MissingDelegateFatalError
  | CorruptImageFatalError
  | FileOpenFatalError
  | BlobFatalError
  | StreamFatalError
  | CacheFatalError
  | CoderFatalError
  | FilterFatalError
  | ModuleFatalError
  | DrawFatalError
  | ImageFatalError
  | WandFatalError
  | RandomFatalError
  | XServerFatalError
  | MonitorFatalError
  | RegistryFatalError
  | ConfigureFatalError
  | PolicyFatalError

external magick_exception_info_reason : exception_info -> string
  = "caml_magick_exception_info_reason"

external magick_exception_info_description : exception_info -> string
  = "caml_magick_exception_info_description"

external magick_exception_info_severity : exception_info -> exception_type
  = "caml_magick_exception_info_severity"

let exception_severity_string = function
  | UndefinedException          -> "UndefinedException"
  | WarningException            -> "WarningException"
  | TypeWarning                 -> "TypeWarning"
  | OptionWarning               -> "OptionWarning"
  | DelegateWarning             -> "DelegateWarning"
  | MissingDelegateWarning      -> "MissingDelegateWarning"
  | CorruptImageWarning         -> "CorruptImageWarning"
  | FileOpenWarning             -> "FileOpenWarning"
  | BlobWarning                 -> "BlobWarning"
  | StreamWarning               -> "StreamWarning"
  | CacheWarning                -> "CacheWarning"
  | CoderWarning                -> "CoderWarning"
  | FilterWarning               -> "FilterWarning"
  | ModuleWarning               -> "ModuleWarning"
  | DrawWarning                 -> "DrawWarning"
  | ImageWarning                -> "ImageWarning"
  | WandWarning                 -> "WandWarning"
  | RandomWarning               -> "RandomWarning"
  | XServerWarning              -> "XServerWarning"
  | MonitorWarning              -> "MonitorWarning"
  | RegistryWarning             -> "RegistryWarning"
  | ConfigureWarning            -> "ConfigureWarning"
  | PolicyWarning               -> "PolicyWarning"
  | ErrorException              -> "ErrorException"
  | TypeError                   -> "TypeError"
  | OptionError                 -> "OptionError"
  | DelegateError               -> "DelegateError"
  | MissingDelegateError        -> "MissingDelegateError"
  | CorruptImageError           -> "CorruptImageError"
  | FileOpenError               -> "FileOpenError"
  | BlobError                   -> "BlobError"
  | StreamError                 -> "StreamError"
  | CacheError                  -> "CacheError"
  | CoderError                  -> "CoderError"
  | FilterError                 -> "FilterError"
  | ModuleError                 -> "ModuleError"
  | DrawError                   -> "DrawError"
  | ImageError                  -> "ImageError"
  | WandError                   -> "WandError"
  | RandomError                 -> "RandomError"
  | XServerError                -> "XServerError"
  | MonitorError                -> "MonitorError"
  | RegistryError               -> "RegistryError"
  | ConfigureError              -> "ConfigureError"
  | PolicyError                 -> "PolicyError"
  | FatalErrorException         -> "FatalErrorException"
  | TypeFatalError              -> "TypeFatalError"
  | OptionFatalError            -> "OptionFatalError"
  | DelegateFatalError          -> "DelegateFatalError"
  | MissingDelegateFatalError   -> "MissingDelegateFatalError"
  | CorruptImageFatalError      -> "CorruptImageFatalError"
  | FileOpenFatalError          -> "FileOpenFatalError"
  | BlobFatalError              -> "BlobFatalError"
  | StreamFatalError            -> "StreamFatalError"
  | CacheFatalError             -> "CacheFatalError"
  | CoderFatalError             -> "CoderFatalError"
  | FilterFatalError            -> "FilterFatalError"
  | ModuleFatalError            -> "ModuleFatalError"
  | DrawFatalError              -> "DrawFatalError"
  | ImageFatalError             -> "ImageFatalError"
  | WandFatalError              -> "WandFatalError"
  | RandomFatalError            -> "RandomFatalError"
  | XServerFatalError           -> "XServerFatalError"
  | MonitorFatalError           -> "MonitorFatalError"
  | RegistryFatalError          -> "RegistryFatalError"
  | ConfigureFatalError         -> "ConfigureFatalError"
  | PolicyFatalError            -> "PolicyFatalError"

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

external magick_image_edge : image -> radius:float -> exception_info -> image
  = "caml_magick_image_edge"

(* visual-effects *)

external magick_image_charcoal : image -> radius:float -> sigma:float -> exception_info -> image
  = "caml_magick_image_charcoal"

(* enhance *)

external magick_image_modulate : image -> modulate:string -> unit
  = "caml_magick_image_modulate"

(* resize *)

external magick_image_scale : image -> int * int -> exception_info -> image
  = "caml_magick_image_scale"

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

external magick_draw_info_set_fill: draw_info -> color -> unit = "caml_magick_draw_info_set_fill"
external magick_draw_info_set_stroke: draw_info -> color -> unit = "caml_magick_draw_info_set_stroke"

external magick_draw_info_set_stroke_width: draw_info -> float -> unit = "caml_magick_draw_info_set_stroke_width"
external magick_draw_info_set_primitive: draw_info -> string -> unit = "caml_magick_draw_info_set_primitive"

external magick_draw_info_set_font: draw_info -> string -> unit = "caml_magick_draw_info_set_font"
external magick_draw_info_set_pointsize: draw_info -> float -> unit = "caml_magick_draw_info_set_pointsize"

external magick_image_draw: image -> draw_info -> unit = "caml_magick_image_draw"

(* quantum *)

external magick_get_quantum_depth: unit -> int = "caml_magick_get_quantum_depth"
external magick_get_quantum_range: unit -> float = "caml_magick_get_quantum_range"
external magick_get_quantum_scale: unit -> float = "caml_magick_get_quantum_scale"

external magick_get_max_map: unit -> int = "caml_magick_get_max_map"
external magick_get_max_colormap_size: unit -> int = "caml_magick_get_max_colormap_size"


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

  let new_image w h color =
    let nf = Magick._magick_image_info_clone () in
    let img = Magick.magick_image_new nf w h color in
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

  let image_edge img ~radius =
    let e = Magick._magick_exception_info_acquire () in
    let img2 = Magick.magick_image_edge img ~radius e in
    Magick._magick_exception_info_destroy e;
    Gc.finalise Magick.magick_image_destroy img2;
    (img2)


  let image_scale img ~size =
    let e = Magick._magick_exception_info_acquire () in
    let img2 = Magick.magick_image_scale img size e in
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

  (* draw *)

  module Color = struct
    type t = int * int * int * int

    let map8 (r, g, b, a) =
      let m =
        match Magick.magick_get_quantum_depth () with
        | 8  -> 1
        | 16 -> 257
        | 32 -> 16843009
        | 64 -> failwith "quantum-depth not handled yet"
        | _ -> invalid_arg "unknown quantum_depth"
      in
      (r * m, g * m, b * m, a * m)
  end

  module Prim = struct
    type t = string

    let draw_line (x1, y1) (x2, y2) =
      (Printf.sprintf "line %d,%d %d,%d" x1 y1 x2 y2)

    let draw_point (x, y) =
      (Printf.sprintf "point %d,%d" x y)

    let draw_rectangle (x, y) (w, h) =
      (Printf.sprintf "rectangle %d,%d %d,%d" x y (x + w) (y + h))

    let draw_circle (cx, cy) (r) =
      (Printf.sprintf "circle %d,%d %d,%d" cx cy cx (cy + r))

    let draw_ellipse (cx, cy) (rx, ry) =
      (Printf.sprintf "ellipse %d,%d %d,%d 0,360" cx cy rx ry)

    let draw_qbcurve (x1, y1) (x2, y2) (x3, y3) =
      (Printf.sprintf "path 'M %d,%d Q %d,%d %d,%d'" x1 y1 x2 y2 x3 y3)

    let draw_cbcurve (x1, y1) (x2, y2) (x3, y3) (x4, y4) =
      (Printf.sprintf "path 'M %d,%d C %d,%d %d,%d %d,%d'" x1 y1 x2 y2 x3 y3 x4 y4)

    let draw_polygon ps =
      let ps = List.map (fun (x, y) -> Printf.sprintf "%d,%d" x y) ps in
      (Printf.sprintf "polygon %s" (String.concat " " ps))

    let draw_arc (cx, cy) (rx, ry) (a1, a2) =
      (Printf.sprintf "ellipse %d,%d %d,%d %d,%d" cx cy rx ry a1 a2)

    let draw_text (x, y) s =
      (Printf.sprintf "text %d,%d '%s'" x y s)
  end

  let fill_primitive img ~prim:p ?fill () =
    let d = Magick.magick_draw_info_acquire () in
    begin match fill with None -> ()
    | Some c -> Magick.magick_draw_info_set_fill d c
    end;
    Magick.magick_draw_info_set_primitive d p;
    Magick.magick_image_draw img d;
    Magick.magick_draw_info_destroy d;
    ()

  let stroke_primitive img ~prim:p ?stroke ?stroke_width () =
    let d = Magick.magick_draw_info_acquire () in
    begin match stroke_width with None -> ()
    | Some v -> Magick.magick_draw_info_set_stroke_width d v
    end;
    begin match stroke with None -> ()
    | Some c -> Magick.magick_draw_info_set_stroke d c
    end;
    Magick.magick_draw_info_set_primitive d p;
    Magick.magick_image_draw img d;
    Magick.magick_draw_info_destroy d;
    ()

  let draw_text img ~pos ~s ?font ?pointsize ?fill ?stroke ?stroke_width () =
    let d = Magick.magick_draw_info_acquire () in
    begin match fill with None -> ()
    | Some c -> Magick.magick_draw_info_set_fill d c
    end;
    begin match stroke with None -> ()
    | Some c -> Magick.magick_draw_info_set_stroke d c
    end;
    begin match stroke_width with None -> ()
    | Some v -> Magick.magick_draw_info_set_stroke_width d v
    end;
    begin match font with None -> ()
    | Some f -> Magick.magick_draw_info_set_font d f
    end;
    begin match pointsize with None -> ()
    | Some p -> Magick.magick_draw_info_set_pointsize d p
    end;
    Magick.magick_draw_info_set_primitive d (Prim.draw_text pos s);
    Magick.magick_image_draw img d;
    Magick.magick_draw_info_destroy d;
    ()
end

include Low_level

