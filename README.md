# Poems

I created a C language console application to help Mama Bunny collect and manage Easter watering poems, which are traditionally used on Easter Monday. The program provides a menu-based interface that allows the user to add new poems, list existing poems, modify a selected poem, and delete poems if needed. All poems are stored in a text file, ensuring persistence between program runs.

The application uses file handling in C to read from and write to a data file, and it includes logic to dynamically manage the poems in memory using arrays and standard input/output operations. When the program starts, it loads the poems from the file into memory. Users interact with a numbered menu to perform actions. When modifications are made—such as adding or deleting a poem—the program updates the file to reflect the changes. Input is validated, and all operations are performed in a loop until the user chooses to exit.

The program was developed to run on Linux systems, including the opsys.inf.elte.hu environment, and it uses standard C libraries only, making it portable and lightweight. Overall, the application supports all the core functions needed for Easter poem management, in a user-friendly terminal interface.

How to Use:

1. Compile the program using a C compiler (e.g., `gcc mama_bunny.c -o bunny`).
2. Run the program in a Linux terminal (`./bunny`).
3. Use the menu to:
   - Add a new poem  
   - List all poems  
   - Modify an existing poem  
   - Delete a poem  
4. Poems are saved to a file automatically.  
5. Exit the program from the menu when done.
