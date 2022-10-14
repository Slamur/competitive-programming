morse = [
    '.-',
    '-...',
    '-.-.',
    '-..',
    '.',
    '..-.',
    '--.',
    '....',
    '..',
    '.---',
    '-.-',
    '.-..',
    '--',
    '-.',
    '---',
    '.--.',
    '--.-',
    '.-.',
    '...',
    '-',
    '..-',
    '...-',
    '.--',
    '-..-',
    '-.--',
    '--..'
]

s = input()

codes = []
for ch in s:
    code = morse[ord(ch) - ord('a')]
    codes.append(code)

encoded = ''.join(codes)

is_p = (encoded == encoded[::-1])
print('YES' if is_p else 'NO')

