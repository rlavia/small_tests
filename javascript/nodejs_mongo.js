module.exports.DataAccessLayer = function () {
    var that;
    that = {};
    that.connectionURL = &amp;quot;mongodb://localhost:27017/mydb&amp;quot;;
    that.mongoClient = require('mongodb').MongoClient;
    //
    //Return data from a collection based on a where clause
    that.select = function(collectionName, where, callback) {
        console.log(&amp;quot;DataAccessLayer.select()&amp;quot;);
        var collection;
        that.mongoClient.connect(that.connectionURL, function(err, db) {
            collection = db.collection(collectionName);
            collection.find(where).toArray(function(err, items) {
                callback(items);
            });
        });
    }
    //
    //Insert a new object into a collection
    that.insert = function(collectionName, obj) {
        console.log(&amp;quot;DataAccessLayer.insert()&amp;quot;);
        var collection;
        :that.mongoClient.connect(that.connectionURL, function(err, db) {
            collection = db.collection(collectionName);
            collection.insert(obj, { w: 0 });
        });
    }
    //
    //Update an object in a collection
    that.update = function(collectionName, obj) {
        console.log(&amp;quot;DataAccessLayer.update()&amp;quot;);
        var collection;
        var query;
        that.mongoClient.connect(that.connectionURL, function(err, db) {
            collection = db.collection(collectionName);
            query = { _id: obj._id };
            collection.update(query, obj, { u: 0, m: 0, w: 0 });
        });
    }
    //
    //Remove one object from a collection
    that.delete = function (collectionName, _id ) {
        console.log(&amp;quot;DataAccessLayer.delete()&amp;quot;);
        var collection;
        var query;
        that.mongoClient.connect(that.connectionURL, function(err, db) {
            collection = db.collection(collectionName);
            query = { _id: _id };
            collection.remove(query, {w: 0});
        });
    }
    //
    return that;
}

