# Function to VALIDATE the phone number of the user
validatePhone() {
    if [[ "$1" =~ ^[0-9]{10}$ ]]; then
        return 0
    else
        return 1
    fi
}

# Function to VALIDATE the gmail of the user
validateEmail() {
    if [[ "$1" =~ ^[a-zA-Z0-9._%+-]+@gmail\.com$ ]]; then
        return 0
    else
        return 1
    fi
}


# Function to create the address hotel file
createAddressHotel(){
    if [ ! -e address_hotel.txt ]; then
        touch address_hotel.txt
    fi
    echo "| Name | Email | Phone Number | Address |" > address_hotel.txt
}
 
# Function to view the address hotel
viewAddressHotel(){
    if [ ! -e address_hotel.txt ]; then
        echo "Address Hotel is Not Created. First Create Address Hotel"
        return
    fi
 
    if [ -s address_hotel.txt ]; then
        cat address_hotel.txt 
#         cat prints a file's content to the
#         standard output:
    else
        echo "Address Hotel is Empty"
    fi
}
 
# Function to insert a record into the address hotel
insertRecordAddressHotel(){
    if [ ! -e address_hotel.txt ]; then
        echo "Address Hotel is Not Created. First Create Address Hotel"
        return
    fi
 
    read -p "Enter Name: " name

    echo "Please enter an email address:"
    read email_address

    # Validate the email address
    if validateEmail "$email_address"; then
       echo "The email address is valid and ends with @gmail.com."
    else
       echo "The email address is invalid or does not end with @gmail.com."
    fi

    echo "Please enter a 10-digit phone number:"
    read phone_number

    if validatePhone "$phone_number"; then
       echo "The phone number is valid."
    else
       echo "The phone number is invalid. Please enter exactly 10 digits."
    fi
    read -p "Enter Address: " address
 
    echo "| $name | $email | $phone | $address |" >> address_hotel.txt
}
 
# Function to delete a record from the address hotel
deleteRecordAddressHotel(){
    if [ ! -e address_hotel.txt ]; then
        echo "Address Hotel is Not Created. First Create Address Hotel"
        return
    fi
 
    read -p "Enter Name: " name
    if [ -z "$(grep -i $name address_hotel.txt)" ]; then
        echo "Record Not Found"
    else
        sed -i "/$name/d" address_hotel.txt
    fi
}
 
# Function to search for a record in the address hotel
searchRecordAddressHotel(){
    if [ ! -e address_hotel.txt ]; then
        echo "Address Hotel is Not Created. First Create Address Hotel"
        return
    fi
 
    read -p "Enter Name: " name
    if [ -z "$(grep -i $name address_hotel.txt)" ]; then
        echo "Record Not Found"
    else
        grep -i $name address_hotel.txt
    fi
}
 
# Function to update a record in the address hotel
updateRecordAddressHotel(){
    if [ ! -e address_hotel.txt ]; then
        echo "Address Hotel is Not Created. First Create Address Hotel"
        return
    fi
 
    read -p "Enter Name: " name
 
    if [ -z "$(grep -i $name address_hotel.txt)" ]; then
        echo "Record Not Found"
        return
    fi
 
    sed -i "/$name/d" address_hotel.txt
    read -p "Enter Email: " email
    read -p "Enter Phone Number: " phone
    read -p "Enter Address: " address
    echo "| $name | $email | $phone | $address |" >> address_hotel.txt
}
 
# Main function to display the menu and handle user input
main(){
    while true; do
        echo -e "\nWelcome to Address Hotel\n"
        echo "1. Create Address Hotel"
        echo "2. View Address Hotel"
        echo "3. Insert Record"
        echo "4. Delete Record"
        echo "5. Search Record"
        echo "6. Update Record"
        echo -e "7. Exit\n"
 
        read -p "Enter Choice: " choice
 
        case $choice in
            1)
            createAddressHotel
            ;;
            2)
            viewAddressHotel
            ;;
            3)
            insertRecordAddressHotel
            ;;
            4)
            deleteRecordAddressHotel
            ;;
            5)
            searchRecordAddressHotel
            ;;
            6)
            updateRecordAddressHotel
            ;;
            7)
            exit
            ;;
            *)
            echo "Invalid Choice"
            ;;
        esac
    done
}
 
# Run the main function
main