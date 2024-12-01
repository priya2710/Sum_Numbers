import os
import random

# Define the directory to store files
output_dir = "text_files"
os.makedirs(output_dir, exist_ok=True)

# Create 100 files
for i in range(1, 101):
    filename = os.path.join(output_dir, f"{i}.txt")
    with open(filename, "w") as file:
        # Randomly choose the number of integers (between 50 and 250)
        num_integers = random.randint(50, 250)
        # Generate random integers and write to the file
        for _ in range(num_integers):
            file.write(f"{random.randint(1, 1000)}\n")  # Integers between 1 and 1000

print(f"100 text files created in the directory '{output_dir}'.")
