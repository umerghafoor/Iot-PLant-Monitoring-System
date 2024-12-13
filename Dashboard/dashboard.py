import dash
from dash import dcc, html
from dash.dependencies import Input, Output

app = dash.Dash(__name__)

app.layout = html.Div([
    dcc.Graph(id='live-update-graph'),
    dcc.Interval(
        id='interval-component',
        interval=1*1000,  # Update every second
        n_intervals=0
    )
])

# Placeholder for MQTT data
mqtt_data = []

@app.callback(Output('live-update-graph', 'figure'),
              Input('interval-component', 'n_intervals'))
def update_graph_live(n):
    global mqtt_data

    # Create a simple line chart
    fig = {
        'data': [{
            'x': list(range(len(mqtt_data))),
            'y': mqtt_data,
            'type': 'line'
        }],
        'layout': {
            'title': 'Live Data'
        }
    }

    return fig

if __name__ == '__main__':
    app.run_server(debug=True)
