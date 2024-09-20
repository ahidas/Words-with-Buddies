import { useRef, useState } from "react";



export function UserForm( {loggedIn, setLoggedIn, vals, curr_board} ){
    const [showSignUp,setShowSignUp] = useState(false);
    const [showLogin,setShowLogin] = useState(false);

    async function save_board(){
      let board_name = "";
      if (curr_board.current === ""){
        board_name = prompt('Enter a name for your board (note: names longer than 15 chars will be shortened)');
      } else {
        board_name = curr_board.current;
      }
     
      let data = {"name" : board_name, "vals" : vals};
      const result = await fetch("http://127.0.0.1:5006/api/save_board",{method: 'POST', credentials: 'include', body: JSON.stringify(data)});
      const js = await result.json();
      console.log(js);
      if(js === true){
        alert("board saved");
      } else {
        alert("error saving board, please try again");
      }
    }


    return (<div className="user_form">
      {showSignUp ? <SignUp setShowSignUp = {setShowSignUp} setLoggedIn = {setLoggedIn} curr_board={curr_board} /> : loggedIn ? null : <button onClick={() => { setShowSignUp(true); setShowLogin(false); }}> Sign Up </button> }
      {showLogin ? <Login setShowLogin = {setShowLogin}  setLoggedIn = {setLoggedIn}/> : loggedIn ? null : <button onClick={ () => { setShowLogin(true); setShowSignUp(false)}}> Login </button> }
      {loggedIn ? <button onClick={ () => save_board()}> Save Board </button> : null}
      {loggedIn ? <button onClick={ () => setLoggedIn(false)}> Sign Out </button> : null}
    </div>)
}

function SignUp( { setShowSignUp, setLoggedIn, curr_board }){
    const Username = useRef("");
    const Password = useRef("");
    async function handleSubmit(e){
            //disable page from reloading
        e.preventDefault();
        const data = JSON.stringify({"username": Username.current, "password": Password.current});
          //getting updates
        const result = await fetch("http://127.0.0.1:5006/api/sign_up",{method: 'POST', credentials: 'include', body: data});
        const js = await result.json();
        console.log(js);
        if(js === true){
            alert("Successfully signed up");
            setLoggedIn(true);
            setShowSignUp(false);
            curr_board.current = "";
        }
    }
    return (<div>
        <header> Sign Up </header>
        <form className="user_form" onSubmit={handleSubmit}> 
        <input className = "user_form_input" type="text" placeholder='Username' 
        onChange={(e) => {
      if (e.target.value.length <= 15) {
        Username.current = e.target.value;
          }
        }}
        />
        <input className = "user_form_input" type="text" placeholder='Password' 
                onChange={(e) => {
                    if (e.target.value.length <= 15) {
                      Password.current = e.target.value;
                        }
                      }}
                      />
        <button> Sign up</button>
        </form>
        <button onClick={() => setShowSignUp(false)}> Close </button>
    </div>)
}

function Login( { setShowLogin, setLoggedIn }){
    const Username = useRef("");
    const Password = useRef("");
    async function handleSubmit(e){
            //disable page from reloading
        e.preventDefault();
        const data = JSON.stringify({"username": Username.current, "password" : Password.current});
          //getting updates
        const result = await fetch("http://127.0.0.1:5006/api/login",{method: 'POST', credentials: 'include', body: data});
        const js = await result.json();
        console.log(js);
        if(js === true){
            alert("Successfully logged in");
            setLoggedIn(true);
            setShowLogin(false);
        }
    }
    return (<div>
        <header> Login </header>
        <form className="user_form" onSubmit={handleSubmit}> 
        <input className = "user_form_input" type="text" placeholder='Username' 
        onChange={(e) => {
      if (e.target.value.length <= 15) {
        Username.current = e.target.value;
          }
        }}
        />
        <input className = "user_form_input" type="text" placeholder='Password' 
                onChange={(e) => {
                    if (e.target.value.length <= 15) {
                      Password.current = e.target.value;
                        }
                      }}
                      />
        <button> Login </button>
        </form>
        <button onClick={ () => setShowLogin(false)}> Close </button>
    </div>)
}