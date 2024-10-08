open Magick

let () =
  let img = Magick.image_read "rose:" in

  Magick.image_display img;
  Magick.image_equalize img;
  Magick.image_display img;
;;
