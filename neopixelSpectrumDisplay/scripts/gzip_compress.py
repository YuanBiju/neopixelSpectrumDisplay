import gzip

files = [
    'web/index.html'
]


def compress_files():
    for file in files:
        print(f'compressing file: {file}')
        with open(file, 'rb') as input, gzip.open(f"{file}.gz", 'wb') as output:
            output.writelines(input)


compress_files()