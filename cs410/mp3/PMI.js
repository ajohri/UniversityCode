/* Map Function 1 */
var MyPMIMap1 = function() {
    // get the additionalInfo attribute/field of the resume (it contains sentences with text)
    var additionalInfo = this.additionalInfo;
    
    // only do stuff if non-empty (has some words)
    if (additionalInfo.length > 0) {
        // clean up the string - lowercase all chars
        additionalInfo = additionalInfo.toLowerCase();
        
        // clean up the string - remove the punctuation
        additionalInfo = additionalInfo.replace(/[.,\/#!?$%\^&\*;:•●{}=\-_`~()]/g,"");
        
        // iterate over words in a document
        var additionalInfo_worded = additionalInfo.split(" ").filter(Boolean);
        
        // get all the pair of subsequent words in the string
        var subSeqWords = [];
        for (var i = 0; i < additionalInfo_worded.length-1; i++) {
            subSeqWords.push([additionalInfo_worded[i], additionalInfo_worded[i+1]]);
        }
        
        // build an array of all the unique words + unique pairs of words
        var uniqueWordsPairs = [];
        
        // use associative array with: word => word_count
        // build a list of all unique words
        var wCount = {};
        
        for (var j = 0; j < additionalInfo_worded.length; j++) {
            // add the word to the dictionary: word => count
            var k = additionalInfo_worded[j];
            
            if (k.length > 0) {
                if (!wCount[k]) {
                    wCount[k] = 0;
                    // w1,$
                    uniqueWordsPairs.push(k + ",$");
                }

                // increment the count
                wCount[k]++;
            }
        }
        
        // create a dictionary for the count of consecutive word pairs: w1 => (word_pair, count)
        var pairCount = {};
        for (var wordIndex = 0; wordIndex < subSeqWords.length; wordIndex++) {
            // add the word pair to the dictionary: "w1,w2" => count
            var k = subSeqWords[wordIndex][0] + "," + subSeqWords[wordIndex][1];
            
            if (!pairCount[k]) {
                pairCount[k] = 0;
                uniqueWordsPairs.push(k);
            }

            // increment the count
            pairCount[k]++;
        }
        
        // iterate through the unique words/word pairs and send count to reduce
        for (var i = 0; i < uniqueWordsPairs.length; i++) {
            var key = uniqueWordsPairs[i];
            // check if individual word
            if (key.split(",")[1].localeCompare('$') == 0) {
                // send to the reducer(s) a tuple (word,$, word_count)
                emit(key, wCount[key.split(",")[0]]);
            }
            else {
                // send to the reducer(s) a tuple (word pair, word_pair_count)
                emit(key, pairCount[key]);
            }
        }
    }
};

var emit = function(key, value) {
    print("key: " + key + "  value: " + tojson(value));
};

/* Reduce Function 1 */
var MyPMIReduce1 = function (key, values) {
    var reducedValue = 0;
    
    // itrate and add up values 
    
    for (var i = 0; i < values.length; i++) {
        reducedValue += values[i];
    }
    
    return reducedValue;
};

/* Map Function 2 */
var MyPMIMap2 = function() {
    // get the _id and value data from the collection
    var id = this._id;
	var key = id.split(",");
	var value = this.value;
	var w1 = key[0];
	var w2 = key[1];
    
    // check if individual word or word pair
    if(w2 != "$") {
		emit(w2, {"pair": id, "count": value});
    }
    
	emit(w1, {"pair": id, "count": value});
};

/* Reduce Function 2 */
var MyPMIReduce2 = function(key, values) {
	var reduced = {"pair": [], "count": []};
    
	for(var i = 0; i < values.length; i++)
	{
        // get the pair and the pair count for each word
		reduced.pair = reduced.pair.concat(values[i].pair);
		reduced.count = reduced.count.concat(values[i].count);
	}
    
	return reduced;
};

/* Map Function 3 */
var MyPMIMap3 = function() {
    // get the _id (word) and value data from the collection
    var id = this._id;
	var value = this.value;
	
    // get the pairs and count values from previous reduce function
	var pairs = value["pair"];
	var counts = value["count"];
    
	for (var i = 0; i < pairs.length; i++)
	{
		if(pairs[i].split(",")[1] == "$")
		{
            // get the individual word and count 
			var indPair = pairs[i];
			var indCount = counts[i];
		}
	}
    
	if(indPair.length < 5) /*error handling*/
		return;
    
	for (var i = 0; i < pairs.length; i++)
	{
        // count all the word pairs and send the individual word to reducer
		if(pairs[i] != indPair[i] && !pairs[i].contains("$")) {
            // iterate through all the word pairs
			emit(pairs[i], { 
                                "word": indPair, 
                                "word_count": indCount,
                                "pair": pairs[i], 
                                "pair_count": counts[i]
                            }
            );
        }
	}
};

/* Reduce Function 3 */
var MyPMIReduce3 = function(key, values) {
	var out = {"PMI": 0, "count": 0};
	var PMI = 0;
	
    var w1Ct = values[0]["word_count"];
	var w2Ct = values[1]["word_count"];
	var pairCt = values[0]["pair_count"];
    
	if(pairCt == NaN) {
        // error check to see if we are given a coutn for the word pair
		PMI = -100000;
    }
	else {
        // caluclate the PMI
		PMI = Math.log((pairCt) / (w1Ct * w2Ct));
    }
    
	out["PMI"]= PMI;
	out["count"]= pairCt;
	return out;
};