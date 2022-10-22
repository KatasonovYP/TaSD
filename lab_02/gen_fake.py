from faker import Faker
from faker.providers import internet
from random import randint
import sys


def gen_theatre() -> dict:
    fake = Faker('en_US')
    min_buff = randint(10, 5000)
    theatre = {
        'name': fake.name(),
        'performance': fake.job(),
        'producer': fake.name(),
        'min': min_buff,
        'max': randint(min_buff, 10000),
        'type_id': randint(0, 2),
    }
    if (theatre['type_id'] == 0):
        theatre.update({
            'age': randint(0, 18),
            'genre': randint(0, 1)
        })
    elif (theatre['type_id'] == 1):
        theatre.update({
            'genre': randint(0, 2)
        })
    elif (theatre['type_id'] == 2):
        theatre.update({
            'composer': fake.name(),
            'country': fake.country(),
            'age':  randint(0, 99),
            'duration': randint(15, 300)
        })
    return theatre


def write_theatre(theatre: dict):
    with open('data.txt', 'a') as file:
        for it in theatre.values():
            if type(it) == str and len(it) > 13:
                it = it[:13]
            file.write(f'{it}\n')


if __name__ == '__main__':
    with open('data.txt', 'w') as f:
        ...
    cnt = 10 if len(sys.argv) == 1 else int(sys.argv[1])
    for i in range(cnt):
        theatre = gen_theatre()
        write_theatre(theatre)
    print(f'gen {cnt} objects')
