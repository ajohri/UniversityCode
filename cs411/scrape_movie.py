from requests import get
from bs4 import BeautifulSoup
import pandas as pd
import re
import inspect

def get_movie_data(url):
    titles=[]
    years=[]
    ratings=[]
    genres=[]
    directors=[]
    stars=[]


    #get html text of url
    response = get(url)
    #print(response)

    #beautiful soup the html text
    html_soup = BeautifulSoup(response.text, 'html.parser')
    #print(html_soup)
    movie_containers = html_soup.find_all('div', class_ = 'lister-item mode-advanced')
    #print(movie_containers)

    #first_movie = movie_containers[0]

    #count = 0
    for movie in movie_containers:

        #print(count)
        #title
        title = movie.h3.a.text
        titles.append(title)
        #print(title)

        #year
        year_string = movie.h3.find('span', class_='lister-item-year').text
        year = re.compile('\d+(?:\.\d+)?')
        year = year.findall(year_string)[0]
        year = int(year)
        years.append(year)
        #print(year)

        #rating
        rating = movie.find(class_='inline-block ratings-imdb-rating')
        rating = float(rating.strong.text)
        ratings.append(rating)
        #print(rating)

        #genre
        genre = movie.p.find('span', class_='genre').text
        genre = genre.strip('\n')
        genre = genre.strip()
        genre = genre.split(', ')
        genres.append(genre)
        #print(genre)

        #director
        director = movie.find('div', class_ = 'lister-item-content')
        director = director.find_all('p')[2]
        #some movies do not have directors
        if(director.find('a'!=None)):
            director = director.find('a').text

        else:
            director = None

        directors.append(director)

        #print(director)

        #stars
        star_html = movie.find('div', class_ = 'lister-item-content')
        star_html = star_html.find_all('p')[2]
        star_html = star_html.find_all('a')[1:]

        #there are multiple star actors in a movie so we need to make a list of actors for each movie then append to overall list of actors
        star=list()

        for s in star_html:
            star.append(s.text)

        stars.append(star)
        #print(star)

        #count+=1


    test_df = pd.DataFrame({'Title': titles,
                            'Year': years,
                            'Rating': ratings,
                            'Genre': genres,
                            'Director': directors,
                            'Stars': stars})
    #print('after each page')
    #print(test_df)
    return(test_df)


def get_all_pages(url, list_):

    while True:

        response = get(url)
        html_soup = BeautifulSoup(response.text, 'html.parser')

        next_page = html_soup.find('a', class_='lister-page-next next-page')
        print(next_page)
        #checks if next page exists
        if not bool(next_page):
            break

        next_page = next_page['href']
        url = 'http://www.imdb.com/search/title'+next_page
        list_.append(get_movie_data(url))

urls = ['http://www.imdb.com/search/title?genres=action&title_type=feature&num_votes=100,&pf_rd_m=A2FGELUUNOQJNL&pf_rd_p=2406822102&pf_rd_r=09KSPJGNTB4V4132EXH1&pf_rd_s=right-6&pf_rd_t=15506&pf_rd_i=top&page=1&sort=moviemeter,asc&ref_=adv_nxt',
       'http://www.imdb.com/search/title?genres=comedy&title_type=feature&num_votes=100,&pf_rd_m=A2FGELUUNOQJNL&pf_rd_p=2406822102&pf_rd_r=09KSPJGNTB4V4132EXH1&pf_rd_s=right-6&pf_rd_t=15506&pf_rd_i=top&page=1&sort=moviemeter,asc&ref_=adv_prv',
       'http://www.imdb.com/search/title?genres=drama&title_type=feature&num_votes=1000,&pf_rd_m=A2FGELUUNOQJNL&pf_rd_p=2406822102&pf_rd_r=09KSPJGNTB4V4132EXH1&pf_rd_s=right-6&pf_rd_t=15506&pf_rd_i=top&page=1&sort=moviemeter,asc&ref_=adv_prv',
       'http://www.imdb.com/search/title?genres=sci_fi&title_type=feature&num_votes=100,&pf_rd_m=A2FGELUUNOQJNL&pf_rd_p=2406822102&pf_rd_r=09KSPJGNTB4V4132EXH1&pf_rd_s=right-6&pf_rd_t=15506&pf_rd_i=top&page=1&sort=moviemeter,asc&ref_=adv_prv']

url = urls[2]
dfs = []
get_all_pages(url, dfs)

drama = pd.concat(dfs)

'''
all_genre_dfs = list()

for url in urls[1]:
    dfs = list()

    get_all_pages(url, dfs)

    one_genre = pd.concat(dfs)

    all_genre_dfs.append(one_genre) '''
