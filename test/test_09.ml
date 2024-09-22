open Magick
module Prim = Magick.Prim
module Color = Magick.Color

let () =
  let img = Magick.new_image 80 80 (Color.map8 (255, 255, 0, 0)) in

  Magick.fill_primitive img
    ~prim:(Prim.draw_circle (60, 60) 10)
    ~fill:(Color.map8 (255, 0, 0, 0)) ();

  Magick.stroke_primitive img
    ~prim:(Prim.draw_line (20, 60) (60, 60))
    ~stroke:(Color.map8 (0, 0, 255, 0))
    ~stroke_width:4.0 ();

  Magick.image_display img;
;;
