open Magick

let () =
  let img1 = Magick.image_read "rose:" in
  let img2 = Magick.image_edge img1 ~radius:1.2 in

  Magick.image_display img2;
;;
