/*number of resumes from New York :  6139   */

db.resumes.find({"education.degree": "Certificate"}).count()

/*Result: 12845*/