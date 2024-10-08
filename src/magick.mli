(** An Interface to the Magick-Core *)
(* Interface-file for the magick-core lib.
 * Authors: Monnier Florent (2024)
 * To the extent permitted by law, you can use, modify, and redistribute
 * this file.
 *)

(** {4 genesis / terminus} *)

val magick_core_genesis : unit -> unit
val magick_core_terminus : unit -> unit

(** {4 exception-info} *)

type exception_info

val magick_exception_info_acquire : unit -> exception_info
val magick_exception_info_destroy : exception_info -> unit

(** {4 image-info} *)

type image_info

val magick_image_info_clone : unit -> image_info
val magick_image_info_destroy : image_info -> unit

val magick_image_info_clone_some : image_info -> image_info

val magick_image_info_set_filename : image_info -> string -> unit
val magick_image_info_set_size : image_info -> string -> unit

(**/**)
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
(**/**)

(** {4 image} *)

type image

val magick_image_destroy : image -> unit
val magick_image_set_filename : image -> string -> unit

(** {4 read / write} *)

val magick_image_read : image_info -> exception_info -> image
val magick_image_write : image_info -> image -> unit

(** {4 create} *)

type color = int * int * int * int

val magick_image_new : image_info -> int -> int -> color -> image

(** {4 display} *)

val magick_image_display : image_info -> image -> unit

(** {4 effects} *)

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

val magick_image_edge :
  image -> radius:float -> exception_info -> image

val magick_image_despeckle :
  image -> exception_info -> image

(** {4 visual-effects} *)

val magick_image_charcoal :
  image -> radius:float -> sigma:float -> exception_info -> image

(** {4 enhance} *)

val magick_image_modulate : image -> modulate:string -> unit
(** modulate:(brightness, saturation, hue), default is 100 *)

val magick_image_negate : image -> unit

val magick_image_equalize : image -> unit

(** {4 resize} *)

val magick_image_scale : image -> int * int -> exception_info -> image

(** {4 color-space} *)

module ColorSpace : sig
  type t = RGB | GRAY | CMYK | HSL | CMY | Luv | LCHab | LCHuv
end

val magick_image_colorspace_transform : image -> ColorSpace.t -> unit

(** {4 composite} *)

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

(** {4 draw-info} *)

type draw_info

val magick_draw_info_acquire: unit -> draw_info
val magick_draw_info_destroy: draw_info -> unit

val magick_draw_info_set_fill: draw_info -> color -> unit
val magick_draw_info_set_stroke: draw_info -> color -> unit

val magick_draw_info_set_stroke_width: draw_info -> float -> unit
val magick_draw_info_set_primitive: draw_info -> string -> unit
(**
  {ul
    {- line x1,y1 x2,y2 }
    {- point x,y }
    {- rectangle x1,y1 x2,y2 }
    {- circle cx,cy x,y }
    {- ellipse cx,cy rx,ry 0,360 }
    {- path 'M x1,y1 Q x2,y2 x3,y3' }
    {- path 'M x1,y1 C x2,y2 x3,y3 x4,y4' }
    {- polygon \[x,y\]+ }
  }
*)

val magick_draw_info_set_font: draw_info -> string -> unit
val magick_draw_info_set_pointsize: draw_info -> float -> unit

val magick_image_draw: image -> draw_info -> unit

(** {4 quantum} *)

val magick_get_quantum_depth: unit -> int
val magick_get_quantum_range: unit -> float
val magick_get_quantum_scale: unit -> float

val magick_get_max_map: unit -> int
val magick_get_max_colormap_size: unit -> int


(** {4 high-level} *)

(** higher-level interface *)

module Magick : sig
  (** higher-level module *)

  val image_read : string -> image
  val new_image : int -> int -> color -> image
  val image_display : image -> unit
  val image_write : image -> filename:string -> unit
  val image_charcoal : image -> radius:float -> sigma:float -> image
  val image_blur : image -> radius:float -> sigma:float -> image
  val image_spread : image -> radius:float -> image
  val image_sharpen : image -> radius:float -> sigma:float -> image
  val image_shade : image -> gray:bool -> azimuth:float -> elevation:float -> image
  val image_edge : image -> radius:float -> image
  val image_despeckle : image -> image
  val image_emboss : image -> radius:float -> sigma:float -> image
  val image_colorspace_transform : image -> ColorSpace.t -> unit
  val image_scale : image -> size:int * int -> image
  val image_composite : image -> CompositeOp.t -> image -> int -> int -> unit
  val image_modulate : image -> modulate:(int * int * int) -> unit
  (* modulates: *)
  val image_brightness : image -> int -> unit
  val image_saturation : image -> int -> unit
  val image_hue : image -> int -> unit
  val image_negate : image -> unit
  val image_equalize : image -> unit

  module Color: sig
    type t = color
    (** (r, g, b, a) *)

    val map8 : t -> t
    (** maps entry colors with Q8 values,
        for use with the current compiled quatum *)
  end

  (* primitives *)

  module Prim: sig
    type t
    val draw_point: int * int -> t
    val draw_line: int * int -> int * int -> t
    val draw_rectangle: int * int -> int * int -> t
    val draw_circle: int * int -> int -> t
    val draw_ellipse: int * int -> int * int -> t
    val draw_qbcurve: int * int -> int * int -> int * int -> t
    val draw_cbcurve: int * int -> int * int -> int * int -> int * int -> t
    val draw_polygon: (int * int) list -> t
    val draw_text: int * int -> string -> string
  end

  val fill_primitive: image -> prim:Prim.t ->
    ?fill:Color.t -> unit -> unit

  val stroke_primitive: image -> prim:Prim.t ->
    ?stroke:Color.t ->
    ?stroke_width:float -> unit -> unit

  val draw_text: image -> pos:int * int -> s:string ->
    ?font:string -> ?pointsize:float ->
    ?fill:Color.t ->
    ?stroke:Color.t ->
    ?stroke_width:float -> unit -> unit
end

(** {4 exception-info} *)

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

val magick_exception_info_reason : exception_info -> string
val magick_exception_info_description : exception_info -> string
val magick_exception_info_severity : exception_info -> exception_type
val exception_severity_string : exception_type -> string

