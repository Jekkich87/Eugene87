var myMap = new google.maps.Map();;

var Riadah = { lat: 24.683225, lng: 46.689923 };
        var Alexandria = { lat: 31.213306, lng: 29.939306 };
        var Kuwait = { lat: 29.366083, lng: 47.967111 };

        var marker1 = new google.maps.Marker({ position: Riadah, map: myMap });

        var marker2 = new google.maps.Marker({ position: Alexandria, map: myMap });

        var marker3 = new google.maps.Marker({ position: Kuwait, map: myMap });
    
        var InfoWindow1 = new google.maps.InfoWindow({ content: '<p>Riyadh City, Olaya St.,Al-Rossais Commercial Center</p>' });
        var InfoWindow2 = new google.maps.InfoWindow({ content: '<p>Smouha Barons, Albert Al Awal St. building 6 App# 101, Alexandria, Egypt.</p>' });
        var InfoWindow3 = new google.maps.InfoWindow({ content: '<p>Kuwait, Kuwait City, Qubila Alshuhada St., Alsedah Tower</p>' });
 
        marker1.addListener('mouseover', function open() { InfoWindow1.open(myMap, marker1) }); marker1.addListener('mouseout', function close() { InfoWindow1.close(myMap, marker1) });
        marker2.addListener('mouseover', function open() { InfoWindow2.open(myMap, marker2) }); marker2.addListener('mouseout', function close() { InfoWindow2.close(myMap, marker2) });
        marker3.addListener('mouseover', function open() { InfoWindow3.open(myMap, marker3) }); marker3.addListener('mouseout', function close() { InfoWindow3.close(myMap, marker3) });