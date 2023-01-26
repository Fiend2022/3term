from fastapi import FastAPI  # Import FastApi
import uvicorn

app = FastAPI()  # Create an App instance


@app.get("/")  # Written a path operation decorator
async def root():
    return {"your good friend."}

if __name__ == '__main__':
    uvicorn.run(app='main:app', host="127.0.0.1", port=6754, reload=True)

