until [ "${yn}" == "yes" -o "${yn}" == "YES" ]
do
	read -p "Please input yes/YES to stop this program: " yn
done
echo "OK! Ypu input the correct answer."

