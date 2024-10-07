
let () =
  let qd = Magick.magick_get_quantum_depth () in
  Printf.printf "- quantum-depth: %d\n" qd;

  let qr = Magick.magick_get_quantum_range () in
  Printf.printf "- quantum-range: %f\n" qr;

  let qs = Magick.magick_get_quantum_scale () in
  Printf.printf "- quantum-scale: %f\n" qs;

  let mm = Magick.magick_get_max_map () in
  Printf.printf "- max-map: %d\n" mm;

  let cm = Magick.magick_get_max_colormap_size () in
  Printf.printf "- colormap-size: %d\n" cm;
;;
