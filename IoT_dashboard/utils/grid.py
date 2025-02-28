# utils/grid.py
import streamlit as st
import math
import pandas as pd

from utils import charts
from utils.action_buttons  import operateFan,operateExhaustFan,operateHumidifier,operateHomeVantilater,ButtonText,CurrentData,State
from utils.anedya import anedya_getValue

multiselect = []
select = []

def date_range() -> pd._libs.tslibs.timestamps.Timestamp:
    Datetime_cols=st.columns(2,gap="medium")
    with Datetime_cols[0]:
        start_date=st.date_input("Enter the start date",format="DD/MM/YYYY",key="startDate")
        
        st.write("Enter the start time:")
        time_cols1=st.columns(4,gap="small")
        with time_cols1[0]:
            start_hour=st.number_input("Hour",value=0,placeholder=0,step=1,min_value=0,max_value=23,key="startHour")
        with time_cols1[1]:
            start_min=st.number_input("Minutes",value=0,placeholder=0,step=1,min_value=0,max_value=59,key="startMinutes")
        with time_cols1[2]:
            start_sec=0
        #     start_sec=st.number_input("Seconds",value=0,placeholder=0,step=1,min_value=0,max_value=59,key="startSeconds")

    with Datetime_cols[1]:
        end_date=st.date_input("Enter the end date",value=start_date,format="DD/MM/YYYY",key="endDate",min_value=start_date)
        
        st.write("Enter the end time:")
        time_cols2=st.columns(4,gap="small")
        with time_cols2[0]:
            if end_date==start_date:
                end_hour=st.number_input("Hour",value=23,placeholder=23,step=1,min_value=start_hour,max_value=23,key="endHour")
            else:
                end_hour=st.number_input("Hour",value=23,placeholder=23,step=1,min_value=0,max_value=23,key="endHour")
        with time_cols2[1]:
            if end_date==start_date and start_hour==end_hour:
                end_min=st.number_input("Minutes",value=59,placeholder=59,step=1,min_value=start_min,max_value=59,key="endMinutes")
            else:    
                end_min=st.number_input("Minutes",value=59,placeholder=59,step=1,min_value=0,max_value=59,key="endMinutes")
        with time_cols2[2]:
            end_sec=0
        #     if end_date==start_date and start_hour==end_hour and start_min==end_min:
        #         end_sec=st.number_input("Seconds",value=start_sec+1,placeholder=59,step=1,min_value=start_sec+1,max_value=59,key="endSeconds")
        #     else:
        #         end_sec=st.number_input("Seconds",value=59,placeholder=59,step=1,min_value=0,max_value=59,key="endSeconds")
    
    start_date=pd.Timestamp(day=start_date.day,month=start_date.month,year=start_date.year,hour=start_hour,minute=start_min,second=start_sec)
    end_date=pd.Timestamp(day=end_date.day,month=end_date.month,year=end_date.year,hour=end_hour,minute=end_min,second=end_sec)

    return start_date,end_date

State()
ButtonText()
CurrentData()

def singlegrid():
    global select
    selectbox1=st.columns(4,gap="small")
    with selectbox1[0]:
        select=st.selectbox("Which parameter you want to see?",options=["Temperature","Humidity","Carbon Monoxide","Carbon Dioxide"],index=None,placeholder="Select a parameter")

    start_date, end_date = date_range()
    st.divider()

    with st.container(border=True):
        if select == "Temperature":
            temp=anedya_getValue("temperature")
            st.metric(label="Temperature",value=str(temp[0])+" °C 🌡️")
            st.markdown("<b>Control Fan:</b>",unsafe_allow_html=True)
            st.button(label=st.session_state.FanButtonText, on_click=operateFan)
            charts.TemperatureChart(start_date=start_date,end_date=end_date)
        
        elif select == "Humidity":
            humi=anedya_getValue("humidity")
            st.metric(label="Humidity",value=str(humi[0])+" % 💧🌡️")
            st.markdown("<b>Control Humidifier:</b>",unsafe_allow_html=True)
            st.button(label=st.session_state.HumidifierButtonText, on_click=operateHumidifier)
            charts.HumidityChart(start_date=start_date,end_date=end_date)

        elif select == "Carbon Monoxide":
            co=anedya_getValue("CarbonMonoxide")
            st.metric(label="Carbon Monoxide",value=str(co[0])+" ppm ☁️")
            st.markdown("<b>Control Humidifier:</b>",unsafe_allow_html=True)
            st.button(label=st.session_state.HomeVantilaterButtonText, on_click=operateHomeVantilater)
            charts.TemperatureChart()

        elif select == "Carbon Dioxide":
            co2=anedya_getValue("CarbonDioxide")
            st.metric(label="Carbon Dioxide",value=str(co2[0])+" ppm ☁️")
            st.markdown("<b>Control Humidifier:</b>",unsafe_allow_html=True)
            st.button(label=st.session_state.ExhaustFanButtonText, on_click=operateExhaustFan)
            charts.HumidityChart()

def multigrid():
    global multiselect
    selectbox2=st.columns(4,gap="small")
    with selectbox2[0]:
        multiselect=st.multiselect("Which parameters you want to see?",options=["Temperature","Humidity","Carbon Monoxide","Carbon Dioxide"],default=None,placeholder="Select multiple parameters")

    start_date, end_date = date_range()
    st.divider()

    #calculations
    total_rows=math.ceil(len(multiselect)/2)
    parameters=multiselect
    parameters=set(parameters)
    count=0

    grid=[]
    for _ in range(total_rows):
        grid.append(st.columns(2,gap="small"))

    for row in range(total_rows):
        for col in range(2):
            with grid[row][col]:
                with st.container(border=True):
                    if "Temperature" in parameters and (count<=len(multiselect)):
                        temp=anedya_getValue("temperature")
                        st.metric(label="Temperature",value=str(temp[0])+" °C 🌡️")
                        st.markdown("<b>Control Fan:</b>",unsafe_allow_html=True)
                        st.button(label=st.session_state.FanButtonText, on_click=operateFan)
                        charts.TemperatureChart(start_date=start_date,end_date=end_date)
                        parameters.discard("Temperature")
                        count+=1

                    elif "Humidity" in parameters and (count<=len(multiselect)):
                        humi=anedya_getValue("humidity")
                        st.metric(label="Humidity",value=str(humi[0])+" % 💧🌡️")
                        st.markdown("<b>Control Humidifier:</b>",unsafe_allow_html=True)
                        st.button(label=st.session_state.HumidifierButtonText, on_click=operateHumidifier)
                        charts.HumidityChart(start_date=start_date,end_date=end_date)
                        parameters.discard("Humidity")
                        count+=1

                    elif "Carbon Monoxide" in parameters and (count<=len(multiselect)):
                        co=anedya_getValue("CarbonMonoxide")
                        st.metric(label="Carbon Monoxide",value=str(co[0])+" ppm ☁️")
                        st.markdown("<b>Control Humidifier:</b>",unsafe_allow_html=True)
                        st.button(label=st.session_state.HomeVantilaterButtonText, on_click=operateHomeVantilater)
                        charts.TemperatureChart(start_date=start_date,end_date=end_date)
                        parameters.discard("Carbon Monoxide")
                        count+=1

                    elif "Carbon Dioxide" in parameters and (count<=len(multiselect)):
                        co2=anedya_getValue("CarbonDioxide")
                        st.metric(label="Carbon Dioxide",value=str(co2[0])+" ppm ☁️")
                        st.markdown("<b>Control Humidifier:</b>",unsafe_allow_html=True)
                        st.button(label=st.session_state.ExhaustFanButtonText, on_click=operateExhaustFan)
                        charts.HumidityChart(start_date=start_date,end_date=end_date)
                        parameters.discard("Carbon Dioxide")
                        count+=1
