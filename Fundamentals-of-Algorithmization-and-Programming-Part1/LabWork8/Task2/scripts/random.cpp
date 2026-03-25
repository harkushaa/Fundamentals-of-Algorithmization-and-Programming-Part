#include "./header-files/random.h"

void AddRandomApplicants(int runScriptTimes) {
    const char* script = R"(
import psycopg2
from faker import Faker
import random
from elasticsearch import Elasticsearch

es = Elasticsearch([{'scheme': 'http', 'host': 'YOUR_HOST', 'port': YOUR_PORT}])

fake = Faker('ru_RU')

conn = psycopg2.connect(
    dbname='task2',
    user='task2',
    password='task2task2',
    host='localhost',
    port=5432
)
cursor = conn.cursor()

def calculate_average(grades):
    if not grades:
        return 0.0
    return sum(grades) / len(grades)

def generate_house_apartment_average_grade(house, apartment, average_grade):
    return f"{house} {apartment} {average_grade:.2f}"

def insert_random_data(num_records):
    for _ in range(num_records):
        fullname = fake.name()
        city = fake.city()
        street = str(random.choice([fake.street_name(), random.randint(1, 100), round(random.uniform(1, 100), 2)]))
        house = random.randint(1, 30)
        apartment = random.randint(1, 100)

        cursor.execute('SELECT city_id FROM public.cities WHERE city_name = %s', (city,))
        result = cursor.fetchone()
        if result:
            city_id = result[0]
        else:
            cursor.execute('INSERT INTO public.cities (city_name) VALUES (%s) RETURNING city_id', (city,))
            city_id = cursor.fetchone()[0]

        cursor.execute('''
            SELECT address_id FROM public.address
            WHERE city_id = %s AND street = %s AND house = %s AND apartment = %s
        ''', (city_id, street, str(house), str(apartment)))
        address_result = cursor.fetchone()
        if address_result:
            address_id = address_result[0]
        else:
            cursor.execute('''
                INSERT INTO public.address (city_id, street, house, apartment)
                VALUES (%s, %s, %s, %s) RETURNING address_id
            ''', (city_id, street, str(house), str(apartment)))
            address_id = cursor.fetchone()[0]

        cursor.execute('''
            INSERT INTO public.applicants (fullname, address_id)
            VALUES (%s, %s) RETURNING applicant_id
        ''', (fullname, address_id))
        applicant_id = cursor.fetchone()[0]

        grades = [random.randint(1, 10) for _ in range(random.randint(2, 5))]
        for grade_value in grades:
            cursor.execute('''
                INSERT INTO public.applicant_grades (applicant_id, grade)
                VALUES (%s, %s)
            ''', (applicant_id, grade_value))

        field = generate_house_apartment_average_grade(house, apartment, calculate_average(grades))

        applicant_doc = {
            'fullname': fullname,
            'city': city,
            'street': street,
            'house': house,
            'apartment': apartment,
            'average_grade': calculate_average(grades),
            'house_aparment_average_grade': field
        }

        es.index(index='applicants', id=applicant_id, document=applicant_doc)

insert_random_data(1)

conn.commit()
conn.close()
)";

    while (runScriptTimes--) {
        PyRun_SimpleString(script);
    }
}
