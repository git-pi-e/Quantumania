echo "Add a message?";

read msg;

git add .;
git commit -m "$msg";
echo "Commiting with: $msg"
git push;