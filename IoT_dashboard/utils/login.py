# utils/login.py
import streamlit as st
import time as ts
# from dotenv import load_dotenv
# import os
from utils.global_vars import username, password

# Load environment variables from .env file
# load_dotenv()
# username = os.getenv("USERNAME")
# password = os.getenv("PASSWORD")

def drawLogin():
    global username, password
    titlecol = st.columns([1, 0.8, 1], gap='small')
    with titlecol[1]:
        st.title("Anedya Dashboard", anchor=False)
        username_inp = st.text_input("Username")
        password_inp = st.text_input("Password", type="password")
        submit_button = st.button(label="Log In")

        if submit_button:
            if username_inp == username and password_inp == password:
                st.success("Login Successful",icon="✅")
                ts.sleep(1)
                st.session_state.LoggedIn = True
                st.rerun()
            else:
                st.error("Invalid Credentials!",icon="⚠️")
