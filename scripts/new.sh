HTML=$(cat <<-END
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <link rel="stylesheet" href="../assets/global.css" />

    <link rel="stylesheet" href="css/sm.css" media="(max-width: 300px)" />
    <link rel="stylesheet" href="css/md.css" media="(max-width: 600px)" />
    <link rel="stylesheet" href="css/lg.css" media="(max-width: 991px)" />
    <link rel="stylesheet" href="css/ex.css" media="(max-width: 1200px)" />

    <title>New Game</title>

    <script defer src="../assets/global.js"></script>
    <script defer src="js/index.js"></script>
</head>

<body>
    This is New Game

</body>

</html>
END
);

echo "Enter Game Full Name: ";
read fullname;

echo "Enter URL Endpoint: ";
read endpoint;


echo "Initialising Directory...";
mkdir $endpoint;
cd $endpoint;

mkdir assets js css lib;

touch ./js/index.js ./css/index.css ./index.html;

echo $HTML > ./index.html;
echo "Game is Ready!";