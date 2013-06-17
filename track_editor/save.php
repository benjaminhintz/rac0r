<?php


$name = time();
$track = $_POST['track'];
$img = $_POST['image'];
$img = str_replace('data:image/png;base64,', '', $img);
$img = str_replace(' ', '+', $img);
$data = base64_decode($img);
$success_1 = file_put_contents("tracks/" . $name . ".png", $data);
$success_2 = file_put_contents("tracks/" . $name . ".track", $track);

echo $success_1 && $success_2;


?>