import os
import re
import sys

# Regular expression to match #include directives
INCLUDE_PATTERN = re.compile(r'^\s*#\s*include\s*[<"]([^">]+)[">]')

# Set to keep track of included files to prevent multiple inclusions
included_files = set()

def resolve_includes(file_path, base_dir, skip_next=False):
    """
    Recursively resolves #include directives in the given file.

    :param file_path: Path to the current file being processed.
    :param base_dir: Base directory for resolving relative includes.
    :param skip_next: Whether to skip concatenating the next include.
    :return: String with all includes resolved.
    """
    full_path = os.path.join(base_dir, file_path)
    normalized_path = os.path.normpath(full_path)

    # Avoid processing the same file multiple times
    if normalized_path in included_files:
        return '';

    included_files.add(normalized_path)

    try:
        with open(normalized_path, 'r') as f:
            lines = f.readlines()
    except FileNotFoundError:
        return f'/* Warning: Included file not found: {file_path} */\n'

    resolved_content = []
    for line in lines:
        if 'noconcat' in line:
            skip_next = True  # Set flag to skip the next include
            resolved_content.append(line)
            continue

        match = INCLUDE_PATTERN.match(line)
        if match:
            include_file = match.group(1)
            if skip_next:
                skip_next = False  # Reset flag after skipping
                resolved_content.append(line)
            else:
                # Handle only local includes; adjust as needed for system includes
                if line.strip().startswith('#include "'):
                    include_content = resolve_includes(include_file, os.path.dirname(normalized_path))
                    if include_content != '':
                        resolved_content.append(f'\n/* Begin include: {include_file} */\n')
                        resolved_content.append(include_content)
                        resolved_content.append(f'\n/* End include: {include_file} */\n')
                else:
                    # For system includes, leave them as-is or handle differently
                    resolved_content.append(line)
        else:
            resolved_content.append(line)
    return ''.join(resolved_content)

def main():
    if len(sys.argv) != 3:
        print("Usage: python concat-header.py <input_file.c> <output_file.h>")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    base_dir = os.path.dirname(os.path.abspath(input_file))
    input_filename = os.path.basename(input_file)

    resolved = resolve_includes(input_filename, base_dir)

    with open(output_file, 'w') as f:
        f.write(resolved)

    print(f"Resolved includes written to {output_file}")

if __name__ == "__main__":
    main()
