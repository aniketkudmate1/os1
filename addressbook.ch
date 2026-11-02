
#!/bin/bash

file="addressbook.txt"

while true
do
    echo "________________"
    echo "    ADDRESS BOOK"
    echo "________________"
    echo "1)create a address book"
    echo "2)insert a record"
    echo "3)view address book"
    echo "4)delete a record"
    echo "5)modify a record"
    echo "6)exit"

    read -p "enter any choice : " choice

    case "$choice" in
    1)
        touch "$file"
        echo "address book created successfully."
        ;;

    2)
        touch "$file"
        echo " insert a new record "

        read -p "enter id:" id
        read -p "enter name:" name
        read -p "enter city:" city

        if grep -q "^$id," "$file"; then
            echo "id already exits"
        else
            echo "$id,$name,$city" >> "$file"
            echo "ID inserted successfully"
        fi
        ;;

    3)
        if [ -f "$file" ]; then
            echo "____ADDRESS BOOK____"
            cat "$file"
        else
            echo "file not found"
        fi
        ;;

    4)
        if [ -f "$file" ]; then
            read -p "enter id to delete : " id

            if grep -q "^$id," "$file"; then
                grep -v "^$id," "$file" > temp.txt
                mv temp.txt "$file"
                echo "ID deleted succcessfullly"
            else
                echo "id not found"
            fi
        else
            echo "file not found"
        fi
        ;;

    5)
        if [ -f "$file" ]; then
            read -p "enter id to modify:" id

            if grep -q "^$id," "$file"; then
                read -p "enter new name :" name
                read -p "enter new city:" city

                grep -v "^$id," "$file" > temp.txt
                echo "$id,$name,$city" >> temp.txt
                mv temp.txt "$file"

                echo "modify record successfully."
            else
                echo "record not found"
            fi
        else
            echo "file not found"
        fi
        ;;

    6)
        echo "exiting..."
        exit 0
        ;;

    *)
        echo "invalid choice"
        ;;
    esac

    echo
done
