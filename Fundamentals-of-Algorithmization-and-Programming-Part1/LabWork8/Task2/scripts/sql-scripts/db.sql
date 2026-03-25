CREATE TABLE public.cities (
    city_id SERIAL PRIMARY KEY,  
    city_name TEXT NOT NULL
);

CREATE TABLE public.address (
    address_id SERIAL PRIMARY KEY,  
    city_id INTEGER NOT NULL,
    street TEXT,
    house TEXT,
    apartment TEXT,
    FOREIGN KEY (city_id) REFERENCES public.cities(city_id)
);

CREATE TABLE public.applicants (
    applicant_id SERIAL PRIMARY KEY,   
    fullname TEXT,      
    address_id INTEGER,               
    FOREIGN KEY (address_id) REFERENCES public.address(address_id)    
);

CREATE TABLE public.applicant_grades (
    grade_id SERIAL PRIMARY KEY,            
    applicant_id INTEGER NOT NULL,          
    grade INTEGER CHECK (grade BETWEEN 1 AND 10),
    FOREIGN KEY (applicant_id) REFERENCES public.applicants(applicant_id) ON DELETE CASCADE
);
