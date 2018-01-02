/* Map Function */
var MyMap = function() {
    // get the additionalInfo attribute/field of the resume (it contains sentences with text)
    var additionalInfo = this.additionalInfo;
    
    // list of stop words taken from meta file
    var stopWords = ["a", "about", "above", "according", "across", "after", "afterwards", "again", "against", "albeit", "all", "almost", "alone", "along", "already", "also", "although", "always", "am", "among", "amongst", "an", "and", "another", "any", "anybody", "anyhow", "anyone", "anything", "anyway", "anywhere", "apart", "are", "around", "as", "at", "av", "be", "became", "because", "become", "becomes", "becoming", "been", "before", "beforehand", "behind", "being", "below", "beside", "besides", "between", "beyond", "both", "but", "by", "can", "cannot", "canst", "certain", "cf", "choose", "contrariwise", "cos", "could", "cu", "day", "do", "does", "doesn't", "doing", "dost", "doth", "double", "down", "dual", "during", "each", "either", "else", "elsewhere", "enough", "et", "etc", "even", "ever", "every", "everybody", "everyone", "everything", "everywhere", "except", "excepted", "excepting", "exception", "exclude", "excluding", "exclusive", "far", "farther", "farthest", "few", "ff", "first", "for", "formerly", "forth", "forward", "from", "front", "further", "furthermore", "furthest", "get", "go", "had", "halves", "hardly", "has", "hast", "hath", "have", "he", "hence", "henceforth", "her", "here", "hereabouts", "hereafter", "hereby", "herein", "hereto", "hereupon", "hers", "herself", "him", "himself", "hindmost", "his", "hither", "hitherto", "how", "however", "howsoever", "i", "ie", "if", "in", "inasmuch", "inc", "include", "included", "including", "indeed", "indoors", "inside", "insomuch", "instead", "into", "inward", "inwards", "is", "it", "its", "itself", "just", "kind", "kg", "km", "last", "latter", "latterly", "less", "lest", "let", "like", "little", "ltd", "many", "may", "maybe", "me", "meantime", "meanwhile", "might", "moreover", "most", "mostly", "more", "mr", "mrs", "ms", "much", "must", "my", "myself", "namely", "need", "neither", "never", "nevertheless", "next", "no", "nobody", "none", "nonetheless", "noone", "nope", "nor", "not", "nothing", "notwithstanding", "now", "nowadays", "nowhere", "of", "off", "often", "ok", "on", "once", "one", "only", "onto", "or", "other", "others", "otherwise", "ought", "our", "ours", "ourselves", "out", "outside", "over", "own", "per", "perhaps", "plenty", "provide", "quite", "rather", "really", "round", "said", "sake", "same", "sang", "save", "saw", "see", "seeing", "seem", "seemed", "seeming", "seems", "seen", "seldom", "selves", "sent", "several", "shalt", "she", "should", "shown", "sideways", "since", "slept", "slew", "slung", "slunk", "smote", "so", "some", "somebody", "somehow", "someone", "something", "sometime", "sometimes", "somewhat", "somewhere", "spake", "spat", "spoke", "spoken", "sprang", "sprung", "stave", "staves", "still", "such", "supposing", "than", "that", "the", "thee", "their", "them", "themselves", "then", "thence", "thenceforth", "there", "thereabout", "thereabouts", "thereafter", "thereby", "therefore", "therein", "thereof", "thereon", "thereto", "thereupon", "these", "they", "this", "those", "thou", "though", "thrice", "through", "throughout", "thru", "thus", "thy", "thyself", "till", "to", "together", "too", "toward", "towards", "ugh", "unable", "under", "underneath", "unless", "unlike", "until", "up", "upon", "upward", "upwards", "us", "use", "used", "using", "very", "via", "vs", "want", "was", "we", "week", "well", "were", "what", "whatever", "whatsoever", "when", "whence", "whenever", "whensoever", "where", "whereabouts", "whereafter", "whereas", "whereat", "whereby", "wherefore", "wherefrom", "wherein", "whereinto", "whereof", "whereon", "wheresoever", "whereto", "whereunto", "whereupon", "wherever", "wherewith", "whether", "whew", "which", "whichever", "whichsoever", "while", "whilst", "whither", "who", "whoa", "whoever", "whole", "whom", "whomever", "whomsoever", "whose", "whosoever", "why", "will", "wilt", "with", "within", "without", "worse", "worst", "would", "wow", "ye", "yet", "year", "yippee", "you", "your", "yours", "yourself", "yourselves"];
    
    // only do stuff if non-empty (has some words)
    if (additionalInfo.length > 0) {
        // clean up the string - lowercase all chars
        additionalInfo = additionalInfo.toLowerCase();
        
        // clean up the string - remove the punctuation
        additionalInfo = additionalInfo.replace(/[.,\/#!?$%\^&\*;:•●{}=\-_`~()]/g,"");
        
        // iterate over words in a document
        var additionalInfo_worded = additionalInfo.split(" ");
        
        // clean up the string - remove stopwords
        for (var i = 0; i < additionalInfo_worded.length; i++) {
            if (stopWords.indexOf(additionalInfo_worded[i]) > -1) {
                additionalInfo_worded.splice(i, 1);
                
                // adjust the iterator i for every element deletion
                i -= 1;
            }
        }
        
        // use associative array with: word => word_count
        var dict = new Array();
        
        for (var wordIndex = 0; wordIndex < additionalInfo_worded.length; wordIndex++) {
            // add the words to the dictionary
            var k = additionalInfo_worded[wordIndex];
            
            if (k.length > 0) {
                if (!dict[k]) {
                    dict[k] = 0;
                }

                // increment the count
                dict[k]++;
            }
        }
        
        // iterate through the dictionary and send the key to reduce function
        for (var key in dict) {
            // send to the reducer(s) a tuple (word, word_count)
            emit(key, dict[key]);
        }
    }
};

var emit = function(key, value) {
    print("key: " + key + "  value: " + tojson(value));
};

/* Reduce Function */
var MyReduce = function(key, values) {
    // add up the counts for the word
    var totalCt = 0
    
    for (var i = 0; i < values.length; i++) {
        totalCt += values[i];
    }
    
    return totalCt;
};

/*
    Initial top 20 words with highest frequency (excluding spaces):
    "and" - 496792
    "•" - 401250
    "of" - 160029
    "to" - 159210
    "in" - 155086
    "with" - 99890
    "the" - 92252
    "a" - 73692
    "Microsoft" - 68484
    "for" - 65599
    "&" - 56584
    "-" - 56315
    "*" - 55230
    "Skills" - 43562
    "skills" - 42947
    "I" - 38448
    "as" - 36869
    "SKILLS" - 33853
    "Office" - 32222
    "experience" - 32118
    
    Modified top 20 words with highest frequency (excluding spaces):
    "skills" - 168876
    "microsoft" - 70636 
    "management" - 63940 
    "experience" - 54327 
    "office" - 50843 
    "excel" - 46588 
    "word" - 45722 
    "customer" - 37613 
    "work" - 37190 
    "ability" - 35667 
    "service" - 35530 
    "computer" - 33434 
    "team" - 31401 
    "software" - 30662 
    "communication" - 29846 
    "knowledge" - 29713 
    "excellent" - 29085 
    "years" - 26581 
    "proficient" - 26452 
    "systems" - 26313
    
    Comparison:
    In the second set of words we see a better idea of the keywords that we want to see. We no longer consider words like and, of, to, in, and etc. This way we can see the more important words in the document.
*/