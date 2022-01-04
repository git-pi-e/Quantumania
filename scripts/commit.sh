echo "Add a message?";

read message;

git add .;
git commit -m "$message";
git push;