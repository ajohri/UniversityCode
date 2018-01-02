/*
TO RUN THE CODE
db.inverted_index.drop();
db.resumes.mapReduce(MyMapInvIndex, MyReduceInvIndex, {"out" : {"reduce" : "inverted_index"}, "query": { location: 'New York, NY' }});
db.inverted_index.aggregate([
    {$unwind: "$value.docs"},
    {$group: {_id: "$_id", docs: {$push:"$value.docs"}, size: {$sum:1}}},
    {$sort:{size:-1}}]).limit(2);
*/

/* Map Function */
var MyMapInvIndex = function() {
    // get the additionalInfo attribute/field of the resume (it contains sentences with text)
    var additionalInfo = this.additionalInfo;
    
    // list of stop words taken from meta file
    var stopWords = ["\'", "\"", "a", "about", "above", "according", "across", "after", "afterwards", "again", "against", "albeit", "all", "almost", "alone", "along", "already", "also", "although", "always", "am", "among", "amongst", "an", "and", "another", "any", "anybody", "anyhow", "anyone", "anything", "anyway", "anywhere", "apart", "are", "around", "as", "at", "av", "be", "became", "because", "become", "becomes", "becoming", "been", "before", "beforehand", "behind", "being", "below", "beside", "besides", "between", "beyond", "both", "but", "by", "can", "cannot", "canst", "certain", "cf", "choose", "contrariwise", "cos", "could", "cu", "day", "do", "does", "doesn't", "doing", "dost", "doth", "double", "down", "dual", "during", "each", "either", "else", "elsewhere", "enough", "et", "etc", "even", "ever", "every", "everybody", "everyone", "everything", "everywhere", "except", "excepted", "excepting", "exception", "exclude", "excluding", "exclusive", "far", "farther", "farthest", "few", "ff", "first", "for", "formerly", "forth", "forward", "from", "front", "further", "furthermore", "furthest", "get", "go", "had", "halves", "hardly", "has", "hast", "hath", "have", "he", "hence", "henceforth", "her", "here", "hereabouts", "hereafter", "hereby", "herein", "hereto", "hereupon", "hers", "herself", "him", "himself", "hindmost", "his", "hither", "hitherto", "how", "however", "howsoever", "i", "ie", "if", "in", "inasmuch", "inc", "include", "included", "including", "indeed", "indoors", "inside", "insomuch", "instead", "into", "inward", "inwards", "is", "it", "its", "itself", "just", "kind", "kg", "km", "last", "latter", "latterly", "less", "lest", "let", "like", "little", "ltd", "many", "may", "maybe", "me", "meantime", "meanwhile", "might", "moreover", "most", "mostly", "more", "mr", "mrs", "ms", "much", "must", "my", "myself", "namely", "need", "neither", "never", "nevertheless", "next", "no", "nobody", "none", "nonetheless", "noone", "nope", "nor", "not", "nothing", "notwithstanding", "now", "nowadays", "nowhere", "of", "off", "often", "ok", "on", "once", "one", "only", "onto", "or", "other", "others", "otherwise", "ought", "our", "ours", "ourselves", "out", "outside", "over", "own", "per", "perhaps", "plenty", "provide", "quite", "rather", "really", "round", "said", "sake", "same", "sang", "save", "saw", "see", "seeing", "seem", "seemed", "seeming", "seems", "seen", "seldom", "selves", "sent", "several", "shalt", "she", "should", "shown", "sideways", "since", "slept", "slew", "slung", "slunk", "smote", "so", "some", "somebody", "somehow", "someone", "something", "sometime", "sometimes", "somewhat", "somewhere", "spake", "spat", "spoke", "spoken", "sprang", "sprung", "stave", "staves", "still", "such", "supposing", "than", "that", "the", "thee", "their", "them", "themselves", "then", "thence", "thenceforth", "there", "thereabout", "thereabouts", "thereafter", "thereby", "therefore", "therein", "thereof", "thereon", "thereto", "thereupon", "these", "they", "this", "those", "thou", "though", "thrice", "through", "throughout", "thru", "thus", "thy", "thyself", "till", "to", "together", "too", "toward", "towards", "ugh", "unable", "under", "underneath", "unless", "unlike", "until", "up", "upon", "upward", "upwards", "us", "use", "used", "using", "very", "via", "vs", "want", "was", "we", "week", "well", "were", "what", "whatever", "whatsoever", "when", "whence", "whenever", "whensoever", "where", "whereabouts", "whereafter", "whereas", "whereat", "whereby", "wherefore", "wherefrom", "wherein", "whereinto", "whereof", "whereon", "wheresoever", "whereto", "whereunto", "whereupon", "wherever", "wherewith", "whether", "whew", "which", "whichever", "whichsoever", "while", "whilst", "whither", "who", "whoa", "whoever", "whole", "whom", "whomever", "whomsoever", "whose", "whosoever", "why", "will", "wilt", "with", "within", "without", "worse", "worst", "would", "wow", "ye", "yet", "year", "yippee", "you", "your", "yours", "yourself", "yourselves"];
    
    // only do stuff if non-empty (has some words)
    if (additionalInfo.length > 0) {
        // clean up the string - lowercase all chars
        additionalInfo = additionalInfo.toLowerCase();
        
        // clean up the string - remove the punctuation
        additionalInfo = additionalInfo.replace(/[.,\/#!?$%\^&\*;:•●{}=\-_`~()]/g, "");
        
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
            // send to the reducer(s) a tuple (word, docId)
            emit(key, {"docs" : [{"docId": this._id, "TF": dict[key]}] });
        }
    }
};

/* Emit Function */
var emit = function(key, value) {
    print("key: " + key + "  value: " + tojson(value));
};

/* Reduce Function */
var MyReduceInvIndex = function (key, values) {
    var reducedValue = {"docs" : []};
    
    for (var i = 0; i < values.length; i++) {
        reducedValue.docs = reducedValue.docs.concat(values[i].docs);
    }
    // {"_id": "word1", "docs" : [{"docId" : 12, "TF" : 5}, {"docId" : 17, "TF" : 8}, {"docId" : 19, "TF" : 3}])
    return reducedValue;
};