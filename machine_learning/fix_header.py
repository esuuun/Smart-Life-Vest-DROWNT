import re

with open('drownt_model.h', 'r', encoding='utf-8') as f:
    content = f.read()

# Pattern: memcpy(varX, (double[]){a, b, c}, 3 * sizeof(double));
pattern = re.compile(r'memcpy\((\w+),\s*\(double\[\]\)\{([^}]+)\},\s*3\s*\*\s*sizeof\(double\)\);')
matches = pattern.findall(content)
print(f'Total matches found: {len(matches)}')
if matches:
    print('Sample match:', matches[0])

# Replace with set3(varX, a, b, c);
new_content = pattern.sub(r'set3(\1, \2);', content)

# Add set3 helper definition at the top if not present
if 'void set3' not in new_content:
    helper = '''
static inline void set3(double *dst, double a, double b, double c) {
    dst[0] = a;
    dst[1] = b;
    dst[2] = c;
}
'''
    new_content = new_content.replace('void add_vectors', helper + '\nvoid add_vectors')

with open('drownt_model.h', 'w', encoding='utf-8') as f:
    f.write(new_content)

print('Updated drownt_model.h successfully!')
