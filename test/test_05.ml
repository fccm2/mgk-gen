open Magick

let () =
  let img = Magick.image_read "rose:" in

  let img1 = Magick.image_spread img ~radius:5.2 in
  let img2 = Magick.image_sharpen img ~radius:4.1 ~sigma:3.2 in
  let img3 = Magick.image_shade img ~gray:true ~azimuth:3.0 ~elevation:2.8 in
 
  Magick.image_display img1;
  Magick.image_display img2;
  Magick.image_display img3;
;;
