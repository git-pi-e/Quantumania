// https://qrng.anu.edu.au/wp-content/plugins/colours-plugin/get_image_bw.php?_=1639159342235
fetch( "/qt" )
    .then( r => r.text() )
    .then( console.log )