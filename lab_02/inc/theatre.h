#ifndef __THEATRE_H__
#define __THEATRE_H__

#define TABLE_SIZE 4000

typedef struct table table_t;
typedef struct key key_t;
typedef struct theatre theatre_t;
typedef union performance performance_t;
typedef struct price_range price_range_t;
typedef struct kid kid_t;
typedef struct adult adult_t;
typedef struct music music_t;

typedef enum kid_genre
{
    kid_piece,
    kid_fairy
} kid_genre_t;

typedef enum adult_genre
{
    adult_piece,
    adult_drama,
    adult_comedy
} adult_genre_t;

struct kid
{
    int age;
    kid_genre_t genre;
};

struct adult
{
    adult_genre_t genre;
};

struct music
{
    char *composer;
    char *country;
    int min_age;
    int duration;
};

struct price_range
{
    int min;
    int max;
};

union performance
{
    kid_t *kid;
    adult_t *adult;
    music_t *music;
};

typedef enum type_id
{
    kid,
    adult,
    music
} type_id_t;

struct theatre
{
    char *name;
    char *performance;
    char *producer;
    price_range_t *price_range;
    type_id_t type_id;
    performance_t *type;
};

struct key
{
    int id;
    char *name;
};

struct table
{
    theatre_t **theatres;
    key_t **keys;
    int len;
};

#endif // #ifndef __THEATRE_H__
