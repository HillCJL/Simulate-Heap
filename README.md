#README

---

Well it's still a homework.

The project is about how to create a link using an array.

But not only created a link, I also tried making a heap by using an array and then I make the link with this heap.

To make the heap, bit operation is needed.I use an int_64 array to make a heap, the higher 32 bit is to store data, the lower 31 bit to store the array index.The 32nd bit is used to show that whether the area had been used.

Use &(value) to store the data and &(0) to delete the data.

Use &(1) to change the data to 1 no matter what value the data was.