// input number --> num
// position of bit --> n

// Check the nth bit of a number

bitStatus = (num >> n) & 1;

// Set the nth bit of a number

newNum = (1 << n) | num;

// Clear the nth bit of a number

newNum = num & (~(1 << n));

// Toggle the nth bit of a number

newNum = num ^ (1 << n);

// Get the highest order set bit of a number

for(i=0; i<INT_SIZE; i++){
    /* If current bit is set */
    if((num>>i) & 1)
        order = i;
}

// Get the lowest set bit of a number

for(i=0; i<INT_SIZE; i++){
    if((num>>i) & 1){
        order = i;
        break;
    }
}
