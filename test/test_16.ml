open Magick

let () =
  let img = Magick.image_read "rose:" in

  Magick.image_display img;
  Magick.image_solarize img ~threshold:0.001;
  Magick.image_display img;
;;
