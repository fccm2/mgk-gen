open Magick

let () =
  let img1 = Magick.image_read "rose:" in
  let img2 = Magick.image_charcoal img1 ~radius:2.8 ~sigma:2.2 in

  Magick.image_display img2;
;;
(* 
  A second interface, with a second module Magick, inside
  the first one.
  This second module is a higher-level interface (easier
  to use.)
*)
