import os
from types import NoneType
import yaml

DIR_WORK = './func_tests'
DIR_TEMPLATES = f'{DIR_WORK}/templates'
DIR_DATA = f'{DIR_WORK}/data'
PATH_README = f'{DIR_WORK}/readme.md'
STD_IN_ARG = '{DIR_DATA}/{mode}_{num}_in.txt'
STD_OUT_ARG = 'out.txt'


def main():
    clean_dir_data()
    clean_readme(PATH_README, f'{DIR_TEMPLATES}/header_readme.md')
    data = get_data(f'{DIR_TEMPLATES}/tests_data.yaml')
    write_all_tests(data)


def clean_dir_data():
    abs_dir_data = os.path.join(os.path.abspath(os.path.dirname(__file__)),
                                '../data')
    for it in os.listdir(f'{abs_dir_data}'):
        os.remove(f'{abs_dir_data}/{it}')


def clean_readme(path, path_header):
    with open(path_header, 'r') as file:
        header = file.read()
    with open(path, 'w') as file:
        file.write(header)


def get_data(path):
    with open(path, 'r') as stream:
        try:
            data = yaml.safe_load(stream)
        except yaml.YAMLError as exc:
            print(exc)
    return data


def write_all_tests(data):
    for mode in data.keys():
        with open(PATH_README, 'a') as readme:
            readme.write('\n' + data[mode]['header'] + '\n\n')
        for i, test in enumerate(data[mode]['tests']):
            write_test(test, mode, i)


def write_test(test, mode, number):
    num = str(number + 1).zfill(2)
    stdpath = STD_IN_ARG.format(DIR_DATA=DIR_DATA, mode=mode, num=num)
    for stream in test.keys():
        test[stream] = format_str(test[stream], num, stdpath)
        if stream == 'label':
            with open(PATH_README, 'a') as readme:
                readme.write(test[stream])
        else:
            path_to_test = f'{DIR_DATA}/{mode}_{num}_{stream}.txt'
            with open(path_to_test, 'w') as file:
                file.write(test[stream])


def format_str(s, num, stdpath):
    s = to_str(s)
    s = s.format(num=num, std_path_in=stdpath, std_path_out=STD_OUT_ARG)
    s += '\n'
    return s


def to_str(src):
    if type(src) == list:
        src = '\n'.join(str(it) for it in src)
    if type(src) == NoneType:
        src = ''
    if type(src) != str:
        src = str(src)
    return src


if __name__ == '__main__':
    main()
