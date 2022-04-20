const firebaseConfig = {
      //copy your firebase config informations
    apiKey: "AIzaSyDqJk-6ulRqdYozYeUVxdppM6CpDS_76bY",
    authDomain: "feedbackform-iot.firebaseapp.com",
    databaseURL: "https://feedbackform-iot-default-rtdb.firebaseio.com",
    projectId: "feedbackform-iot",
    storageBucket: "feedbackform-iot.appspot.com",
    messagingSenderId: "448782781174",
    appId: "1:448782781174:web:789850e6382d03017a3ad7"
  };

  
  
  // initialize firebase
  firebase.initializeApp(firebaseConfig);
  
  // reference your database
  var contactFormDB = firebase.database().ref("feedbackForm-IOT");
  var ImageURL = firebase.database().ref("Image-URL");


  document.getElementById("contactForm").addEventListener("submit", submitForm);
  
  function submitForm(e) {
    e.preventDefault();
  
    var name = getElementVal("name");
    var emailid = getElementVal("emailid");
    var msgContent = getElementVal("msgContent");
    var number = getElementVal("number");
    var wateravail;
    document.getElementsByName('wateravail').forEach(radio => {
        if(radio.checked){
            wateravail = radio.value;
        }
    });
    var waterleak;
    document.getElementsByName('waterleak').forEach(radio => {
        if(radio.checked){
            waterleak = radio.value;
        }
    });
    var odour;
    document.getElementsByName('odour').forEach(radio => {
        if(radio.checked){
            odour = radio.value;
        }
    });



    saveMessages(name, emailid, msgContent, number, wateravail, waterleak, odour);
  
    //   enable alert
    document.querySelector(".alert").style.display = "block";
  
    //   remove the alert
    setTimeout(() => {
      document.querySelector(".alert").style.display = "none";
    }, 3000);
  
    //   reset the form
    document.getElementById("contactForm").reset();

  }
  
  const saveMessages = (name, emailid, msgContent, number, wateravail, waterleak, odour) => {
    var newContactForm = contactFormDB.push();
  
    newContactForm.set({
      name: name,
      emailid: emailid,
      msgContent: msgContent,
      number: number,
      wateravail: wateravail,
      waterleak: waterleak,
      odour: odour,
 
    });
  };
  
  const getElementVal = (id) => {
    return document.getElementById(id).value;
  };

  
document.getElementById('img').addEventListener('change', (event) => {
  const file = event.target.files[0];
  const storageRef = firebase.storage().ref('images/' + file.name);

  storageRef.put(file)

  setTimeout(function() {

      storageRef.getDownloadURL().then(function(url){


      console.log(url);

       savelink(url);



    
  });
   }, 15000);
});

const savelink = (url) => {
  var newlink = ImageURL.push();

  newlink.set({
    url:url

  });
};

