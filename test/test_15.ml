open Magick

let () =
  let img = Magick.image_read "rose:" in
  Magick.image_display img;

  let img2 = Magick.image_add_noise img LaplacianNoise in
  Magick.image_display img2;

  let img3 = Magick.image_despeckle img2 in
  Magick.image_display img3;
;;
