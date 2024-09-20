open Magick

let () =
  let img1 = Magick.image_read "rose:" in
  let img2 = Magick.image_charcoal img1 ~radius:1.6 ~sigma:1.2 in

  (* Multiply *)
  Magick.image_composite img1 CompositeOp.Lighten img2 0 0;
  Magick.image_display img1;
;;
