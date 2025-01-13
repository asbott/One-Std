import re

def convert_enum(input_file, output_file):
    with open(input_file, 'r') as infile:
        content = infile.read()

    # Match typedef enums
    enum_pattern = re.compile(
        r"typedef\s+enum\s+\w*?\s*{(.*?)}\s*(\w+);",
        re.DOTALL
    )

    # Convert a single enum
    def convert_enum_block(match):
        body = match.group(1).strip()
        enum_name = match.group(2)

        # Convert enum name to This_Case
        this_case_name = re.sub(r'([a-z])([A-Z])', r'\1_\2', enum_name).replace('_', ' ').title().replace(' ', '_')

        # Convert members to SCREAMING_SNAKE_CASE
        def convert_member(line):
            if '=' in line:
                name, value = map(str.strip, line.split('=', 1))
                screaming_snake_name = re.sub(r'([a-z])([A-Z])', r'\1_\2', name).upper()
                return f"{screaming_snake_name} = {value}"
            return line.strip()

        members = [convert_member(line) for line in body.split(',') if line.strip()]
        formatted_members = ',\n    '.join(members)

        return f"typedef enum {this_case_name} {{\n    {formatted_members}\n}} {this_case_name};"

    # Process all enums in the file
    converted_content = enum_pattern.sub(convert_enum_block, content)

    # Write to output file
    with open(output_file, 'w') as outfile:
        outfile.write(converted_content)

# Example usage
convert_enum('spirv.h', 'converted_spirv.h')
