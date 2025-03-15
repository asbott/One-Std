import math

# Constants
TABLE_SIZE = 721

EPSILON = 1e-6

# Linear interpolation (lerp) implementation
def lerp(start, end, t):
    return start + t * (end - start)

# Generate tables
sine_table = [math.sin(lerp(0, math.pi * 2, i / TABLE_SIZE)) for i in range(TABLE_SIZE)]
cosine_table = [math.cos(lerp(0, math.pi * 2, i / TABLE_SIZE)) for i in range(TABLE_SIZE)]
tan_table = [
    0.0 if abs(lerp(0, math.pi, i / TABLE_SIZE) - (math.pi/2)) < EPSILON
    else math.tan(lerp(0, math.pi, i / TABLE_SIZE))
    for i in range(TABLE_SIZE)
]
asine_table = [math.asin(lerp(-1, 1, i / TABLE_SIZE)) for i in range(TABLE_SIZE + 1)]
acosine_table = [math.acos(lerp(-1, 1, i / TABLE_SIZE)) for i in range(TABLE_SIZE + 1)]

# Function to generate C syntax array
def generate_c_table(table_name, table_values):
    c_table = f"unit_local const float64 {table_name}[{len(table_values)}] = {{\n"
    for i, value in enumerate(table_values):
        c_table += f"    {value:.17g},"
        if (i + 1) % 8 == 0:  # Wrap every 8 values
            c_table += "\n"
    c_table = c_table.rstrip(',\n') + "\n};\n"
    return c_table

# Generate C tables
c_sine_table = generate_c_table("sine_table", sine_table)
c_cosine_table = generate_c_table("cosine_table", cosine_table)
c_tan_table = generate_c_table("tan_table", tan_table)
c_asine_table = generate_c_table("asine_table", asine_table)
c_acosine_table = generate_c_table("acosine_table", acosine_table)

# Combine all tables into one C code output
c_code = (
    c_sine_table
    + "\n"
    + c_cosine_table
    + "\n"
    + c_tan_table
    + "\n"
    + c_asine_table
    + "\n"
    + c_acosine_table
)

# Save to file or print
with open("src/trig_tables.h", "w") as file:
    file.write(c_code)

print("C tables generated and saved to 'trig_tables.h'.")
